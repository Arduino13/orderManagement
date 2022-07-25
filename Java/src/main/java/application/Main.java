package application;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.util.Callback;
import javafx.scene.Scene;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Rectangle2D;

import java.sql.SQLException;

import DBwrapper.Database_obj;

public class Main extends Application {
	public static boolean test=false;
	
	BorderPane mainLayout;
	Stage primaryStage_t;
	Scene scene_t;	
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	//if card_number is not null loads screen in fxml form specified by text, else
	//it will load enter screen 
	public boolean set_scene(Stage primaryStage,String text,String card_number){
		try{
			//tries to load the layout
			FXMLLoader loader = new FXMLLoader();
			loader.setLocation(getClass().getResource(text));
			primaryStage_t=primaryStage;
			mainLayout = loader.load();
			
			if(card_number!=null){
				FxmlControl controller = loader.<FxmlControl>getController();
				//implements class that has function for displaying enter screen
				//for example when user logs out
				class SetBackEnter implements EnterScreen{
					@Override
					public void Set(){
						start(primaryStage);
					}
				}
				SetBackEnter enter = new SetBackEnter();
				
				//logs in the user by card_number and moves to main screen
				if(!controller.setUser(card_number)) return false;
				else controller.setEnterScreen(enter);
			}
			else{
				Database_obj db = new Database_obj();
				ObservableList<User> list = db.loadListUser();
				ObservableList<String> list_names = FXCollections.observableArrayList();
				
				for(User u : list){
					list_names.add(u.getName());
				}
				
				AutoCompleteTextField box = new AutoCompleteTextField();
				box.getEntries().addAll(list_names);
				
				ListView<Item> List = (ListView)mainLayout.lookup("#table");
				
				//sets up key listener to move around without mouse
				class KeyTyper{
					int position = 0;
					public void onKey(KeyEvent e){
						if(e.getCode().equals(KeyCode.UP)){
							List.requestFocus();
							List.getSelectionModel().select(0);
							List.getFocusModel().focus(0);
							position = 0;
						}
						else if(e.getCode().equals(KeyCode.DOWN)){
							box.requestFocus();
						}//entering user name 
						else if(e.getCode().equals(KeyCode.ENTER)&&list_names.indexOf(box.getText())!=-1){
							set_scene(primaryStage_t, "/main.fxml",((User)list.get(list_names.indexOf(box.getText()))).getCardNumber());
						}
					}
					public void onKey_L(KeyEvent e){
						if(e.getCode().equals(KeyCode.UP)){
							if(position!=0)position--;
						}
						else if(e.getCode().equals(KeyCode.DOWN)){
							if(position==(List.getItems().size()-1)) onKey(e);
							else if(List.getItems().size()==0) onKey(e);
							else position++;
						}//changing item state from inProgress to pause and opposite
						else if(e.getCode().equals(KeyCode.ENTER)&&List.getItems().size()!=0){
							Item item = List.getItems().get(position);
							try{
								if(item.getClass().toString().equals(CustomCell.ITEM_TYPE)){
									db.saveItem(item.setState(item.getState().getState()==State.inProgress ? new State(State.paused) : new State(State.inProgress)));
									db.saveRecord(item);
								}
								else{
									db.saveControl((Control)item.setState(item.getState().getState()==State.inProgress ? new State(State.paused) : new State(State.inProgress)));
									db.saveControl_h((Control)item);
								}
								setItems(item);
							}catch(SQLException error){
								DialogBoxes.ErrorBox("Error occurred while connecting to database");
								Log.StackTrace(error);
							}
						}
					}
				}
				KeyTyper listner = new KeyTyper();
				
				//sets key listner to GUI components
				box.setOnKeyPressed(value->listner.onKey(value));
				box.setOnKey(value->listner.onKey(value));
				List.setOnKeyPressed(value->listner.onKey_L(value));
				
				((VBox)mainLayout.lookup("#box")).getChildren().add(box);
				box.setId("enter_input");
			}

			//loads the actual screen
			Scene scene = new Scene(mainLayout);
			scene.getStylesheets().add(getClass().getResource("/application.css").toExternalForm());
			scene_t=scene;
			primaryStage_t.setScene(scene);
			
			Screen screen = Screen.getPrimary();
		    Rectangle2D bounds = screen.getVisualBounds();
		    primaryStage.setWidth(bounds.getWidth());
		    primaryStage.setHeight(bounds.getHeight());

		    primaryStage.setMaximized(true);
			primaryStage_t.show();
			
			if(card_number==null) ((AutoCompleteTextField)scene_t.lookup("#enter_input")).requestFocus();
			
			return true;
		}catch (Exception e){
			e.printStackTrace();
			return false;
		}
	}

	//function that is called on start of program 
	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Override
	public void start(Stage primaryStage) {
		try {
			set_scene(primaryStage, "/styl.fxml",null);
			ListView<Item> listView = (ListView)scene_t.lookup("#table"); //supress warning
			listView.setCellFactory(new Callback<ListView<Item>, ListCell<Item>>() {
				@Override
				public ListCell<Item> call(ListView<Item> listView) {
					return new CustomCell(true); //true for displaying user name in last column
				}
			});	
			//sets cell factory similar concept to view-model concept, but
			//cells process their content one by one istead of the model processing
			//data for whole table
			//
			//actuall data are set with function updateItem 
			setItems();
			
			//just for testing 
			if(test){
				scene_t.setOnKeyPressed(event->{
					switch(event.getCode().toString()){
						case "ENTER":
							set_scene(primaryStage_t, "/main.fxml","2323");
							break;
					}
				});
			}
			else{ //user tag is now unused
	    		/*Timer t = new Timer();
	    		t.schedule(new TimerTask() {
	    			@Override
	    			public void run(){
    					iButton button = new iButton();
    					String id = button.readID();
    					if(id!=null){
    						((Text)scene_t.lookup("#enter_text")).setText("Processing");
    						try {
								Thread.sleep(100); 
							} catch (InterruptedException e) {
								Platform.runLater(()->DialogBoxes.ErrorBox("Timer error"));
							}
    						Platform.runLater(()->{
        						boolean loaded=false;
        						loaded=set_scene(primaryStage_t,"main.fxml",id);
        						if(loaded) t.cancel();
    						});
    					}
	    			}
	    		},0,250);*/ 
			}
	        
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void setItems(){
		setItems(null);
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void setItems(Item item){
		Database_obj db = new Database_obj();
		ListView<Item> listView = (ListView)scene_t.lookup("#table"); //supress warning
		
		try{
			ObservableList<Item> items = FXCollections.observableArrayList();
			ObservableList<Control> controls = db.loadListControl();
			ObservableList<Item> items_list = db.loadListItem();
			ObservableList<User> users = db.loadListUser();
			
			for(Control c : controls){
				items_list.add(c);
			}
			
			if(item!=null&&item.getState().getState()==State.inProgress){
				for(Item i : items_list){
					if(i.getUser().getId().equals(item.getUser().getId())&&i.getState().getState()==State.inProgress&&!i.getID().equals(item.getID())){
						i.setState(new State(State.paused));
						if(i.getClass().toString().equals(CustomCell.ITEM_TYPE)){
							db.saveItem(i);
							db.saveRecord(i,true);
						}
						else{
							db.saveControl((Control)i);
							db.saveControl_h((Control)i,true);
						}
					}
				}
			}
			
			for(User u : users){
				if(u.getLast()!=null){
					try{
						Item temp = db.loadItem(u.getLast());
						if(temp.getState().getState()!=State.completed) items.add(temp);
					}catch(IllegalArgumentException e){
						try{
							Control control = db.loadControl(u.getLast());
							if(control.getState().getState()!=State.stopped&&control.getState().getState()!=State.completed) items.add(control);
						}catch(IllegalArgumentException | SQLException error){
							DialogBoxes.ErrorBox("Error occurred while connecting to database");
							Log.StackTrace(error);
						}
					}
				}
			}
			
			listView.setItems(items);
		}catch(SQLException e){
			DialogBoxes.ErrorBox("Error occurred while connecting to database");
			Log.StackTrace(e);
		}
	}
	
	@Override
	public void stop(){
		System.exit(1);
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
