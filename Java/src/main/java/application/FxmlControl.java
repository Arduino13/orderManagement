package application;

import java.math.BigInteger;
import java.net.URL;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.SQLException;
import java.time.*;
import java.time.format.DateTimeFormatter;
import java.util.*;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.input.KeyEvent;
import javafx.util.Callback;
import javafx.util.Pair;
import javafx.scene.input.*;
import DBwrapper.Database_obj;

/*
 * Main screen list of orders and controls created by logged user
 */

//interface for class in Main.java that implements method for displaying enter
//screen
interface EnterScreen{
	void Set();
}

public class FxmlControl implements Initializable{
		private enum position{
			BUTTON,
			TABLE
		}
		
		@FXML
		private ListView<Item> neco;
		@FXML
		private TextArea timeLabel;
		@FXML
		private TextArea dateLabel;
		@FXML
		private Button button_id;
		@FXML
		private TextArea user_area;
		
		//if focus is on button or on table
		private position pos = position.BUTTON;
		private int tablePos = 0;
		
		private Database_obj db = new Database_obj();

		//currently out of service 
		//private iButton button = new iButton();
		
		private User user;
		private KeyCombination keyComb = new KeyCodeCombination(KeyCode.A,KeyCombination.CONTROL_DOWN);
		private KeyCombination logout = new KeyCodeCombination(KeyCode.O,KeyCombination.CONTROL_DOWN);
		
		private EnterScreen screen = null;
		
		//opens AddDialog
		@FXML
		private void buttonPressd(ActionEvent e){
			AddDialog d = new AddDialog(user);
			try{
				setItemsTable(d.id_new_f());
			}catch(SQLException error){
				DialogBoxes.ErrorBox("Chyba spojen� s datab�z�");
				Log.StackTrace(error);
			}
		}
		
		
		//to move around screen without mouse
		@FXML
		private void handleOnKeyPressed(KeyEvent event){
			KeyCode code = event.getCode();
		
			if(code.equals(KeyCode.DOWN)){
				if(pos==position.BUTTON){
					pos=position.TABLE;
					neco.getSelectionModel().select(0);
					neco.getFocusModel().focus(0);
					tablePos=0;
				}
				else if(tablePos<neco.getItems().size()){
					tablePos++;
				}
			}

			if(code.equals(KeyCode.UP)){
				if(pos==position.TABLE&&(tablePos==0)){
					button_id.requestFocus();
					pos=position.BUTTON;
				}
				else if(tablePos!=1||tablePos!=0){
					tablePos--;
				}
			}

			if(code.equals(KeyCode.ENTER)&&pos==position.BUTTON){
				button_id.fire();
			}
			else if(code.equals(KeyCode.ENTER)){
				if(!(neco.getItems().get(tablePos).getState().getState()==State.completed||
						(neco.getItems().get(tablePos).getClass().toString().equals(CustomCell.CONTROL_TYPE)&&neco.getItems().get(tablePos).getState().getState()==State.stopped))){
					setChoice(tablePos);
				}
			}
			
			if(keyComb.match(event)){
				adminInput();
			}
			
			if(logout.match(event)){
				screen.Set();
			}
		}
		
		//opens admin dialog
		private void adminInput(){
			Optional<Pair<String,String>> result = DialogBoxes.InputDialog();
			String hash_password="";
			
			if(result.isPresent()){
				try {
					MessageDigest md = MessageDigest.getInstance("SHA-512");
					byte[] byte_a = md.digest(result.get().getValue().getBytes());
					BigInteger no = new BigInteger(1,byte_a);
					hash_password = no.toString(16);
					
					while(hash_password.length()<32){
						hash_password = "0" + hash_password;
					}
					System.out.print(hash_password);
				} catch (NoSuchAlgorithmException e1) {
					Log.ErrorLog("Internal error see StackTrace");
					Log.StackTrace(e1);
				}
				
				try {
					System.out.print(result.get().equals(db.name));
					if(result.get().getKey().equals(db.name)&&hash_password.equals(db.confLoad("password"))){
						new AdminDialog();
					}
					
					else Platform.runLater(()->DialogBoxes.ErrorBox("Incorrect username or password"));
				} catch (SQLException e) {
					Platform.runLater(()->DialogBoxes.ErrorBox("Error while connecting to database"));
				}
			}
		}
		
		private void setItemsTable() throws SQLException{
			setItemsTable(null);
		}
		
		//loads orders to the table. Item inProgress is order/control for now item 
		//that was marked as in progress so other items will be marked as pause
		private void setItemsTable(Item inProgress) throws SQLException{
			ObservableList<Item> temp = db.loadListItem();
			for(Control c : db.loadListControl()){
				temp.add(c);
			}

			//marking other items as paused
			if(inProgress!=null&&inProgress.getState().getState()==State.inProgress){
				ObservableList<Item> temp_date = temp;
				Item.Compare comp = new Item.Compare(Item.Compare.type.DATE);
				Collections.sort(temp_date,comp);
				for(Item i : temp_date){
					if(!i.getID().equals(inProgress.getID())&&i.getState().getState()==State.inProgress&&i.getUser().getId().equals(user.getId())){
						i.setState(new State(State.paused));
						if(i.getClass().toString().equals(CustomCell.ITEM_TYPE)){
							db.saveItem(i);

							//true for adding delay see database for more info
							//in this case only 2 objects at max are saved 
							db.saveRecord(i,true); 
						}
						else{
							db.saveControl((Control)i);
							db.saveControl_h((Control)i,true);
						}
					}
				}
			}
			

			ObservableList<Item> list = FXCollections.observableArrayList();
			for(Item i : temp){
				if(i.getUser().getId().equals(user.getId())) list.add(i);
			}
			Item.Compare comp = new Item.Compare(Item.Compare.type.STATE);
			Collections.sort(list,comp);
			
			neco.setItems(list);
			neco.getSelectionModel().select(tablePos);
			neco.getFocusModel().focus(tablePos);
		}
		
		//runs state change dialog and saves result
		private void setChoice(int position){
			Optional<String> result = DialogBoxes.ItemChDialog();
			Item item = neco.getItems().get(position);
			
			if(result.isPresent()){
				item.setState(item.getState().setState(State.str2State(result.get())));
			
				if(State.str2State(result.get())==State.completed){
					Date now = Date.from(LocalDateTime.now()
					      .atZone(ZoneId.systemDefault())
					      .toInstant());
				
					item.setDateTo(now);
				}
				
				//in case control is stopped a reason dialog is shown
				if(State.str2State(result.get())==State.stopped&&item.getClass().toString().equals(CustomCell.CONTROL_TYPE)){
					Optional<String> reason = DialogBoxes.ReasonDialog();
					if(result.isPresent()){
						((Control)item).setReason(reason.get());
					}
					
					
					Date now = Date.from(LocalDateTime.now()
						      .atZone(ZoneId.systemDefault())
						      .toInstant());
					
					item.setDateTo(now);
				}
				
				try {
					if(item.getClass().toString().equals(CustomCell.ITEM_TYPE)){

						//because only one item is saved here there is no need for delay
						db.saveItem(item);
						db.saveRecord(item);
					}
					else{
						db.saveControl((Control)item);
						db.saveControl_h((Control)item);
					}

					//save current item for user
					db.saveUser(item.getUser().setLast(item.getID()));
					
					//reloads table
					setItemsTable(item);
				} catch (SQLException e) {
					DialogBoxes.ErrorBox("Error occurred while connecting to database");
					Log.StackTrace(e);
				}
			}
		}
		
		//used by Main.java (enter screen) to set user before actually dispalying
		//the screen 
		public boolean setUser(String card_number){
			try {
				user = db.loadUser_card(card_number);
				return true;
			} catch (SQLException | IllegalArgumentException e) {
				Log.WarningLog("user does not exist "+card_number);		
				try {
					ObservableList<User> list = db.loadListUser();
					if(list.size()==0) adminInput();
				} catch (SQLException e1) {
					DialogBoxes.ErrorBox("Error occurred while connecting to database");
					Log.StackTrace(e1);
				}
				return false;
			}
		}
		
		//sets a class with method Set that displays enter screen
		public void setEnterScreen(EnterScreen enter){
			screen=enter;
		}
		
		private void initTable(){
    		try {
    			setItemsTable();
    			user_area.setText(user.getName());
    		} catch (SQLException e) {
    			DialogBoxes.ErrorBox("Error occurred while connecting to database");
    			Log.StackTrace(e);
    		}
		}
		
	    @Override
	    public void initialize(URL url, ResourceBundle rb) {
	    	//runs later so user data can be loaded 
	    	Platform.runLater(()->{
	    		neco.setCellFactory(new Callback<ListView<Item>, ListCell<Item>>() {
	    			@Override
	    			public ListCell<Item> call(ListView<Item> listView) {
	    				return new CustomCell();
	    			}
	    		});	     
	        
				//updates time on screen
	    		new Timer().schedule(new TimerTask() {
	    			@Override
	    			public void run() {
	    				timeLabel.setText(LocalTime.now().format(DateTimeFormatter.ofPattern("HH:mm:ss")));
	    				dateLabel.setText(LocalDate.now().format(DateTimeFormatter.ofPattern("dd-MM-yyyy")));
	    			}
	    		}, 0, 1000);
	    		
				//waiting for new user tag, for now unused
	    		/*new Timer().schedule(new TimerTask() {
	    			@Override
	    			public void run(){
	    				Platform.runLater(()->{
	    					String id = button.readID();
	    					if(id!=null){
	    						if(setUser(id)) initTable();
	    					}
	    				});
	    			}
	    		},0,250);*/ 
	    		
	    		if(user!=null) initTable();
	    		
	    	});
	    }
	}
