package application;

import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Priority;

//custom cell for list 

public class CustomCell extends ListCell<Item>{
	public static String ITEM_TYPE="class application.Item";
	public static String CONTROL_TYPE="class application.Control";
	
	private TextField state = new TextField();
	private TextField date = new TextField();
	private TextField id = new TextField();
	private TextField type = new TextField();
	private TextField user = new TextField();
	private TextField array[]={id,date,state,type,null};
	
	private GridPane content;
	
	private boolean with_user = false;
	
	public CustomCell(boolean with_user){
		super();
		this.with_user=with_user;
		content = new GridPane();
		int counter=0;
		
		if(with_user) array[4]=user;
		
		for(TextField one : array){
			if(one!=null){
				content.add(one, counter, 0);
				one.setEditable(false);
				one.setFocusTraversable(false);
				GridPane.setHgrow(one, Priority.ALWAYS);
				GridPane.setVgrow(one, Priority.ALWAYS);
				counter++;
			}
		}
	}
	
	public CustomCell(){
		this(false);
	}
	
	@Override
	protected void updateItem(Item item, boolean empty){
		super.updateItem(item, empty);
		if(item != null && !empty){
			date.setText(item.getDateFromS());
			id.setText(String.format("%s",item.getNumber()));
			state.setText(item.getState().toString());
			if(item.getClass().toString().equals(CONTROL_TYPE)) type.setText("Control");
			else type.setText("Rolling");
			
			if(with_user) user.setText(item.getUser().toString());
			
			if(item.getState().getState()==State.completed||
					(item.getClass().toString().equals(CONTROL_TYPE)&&item.getState().getState()==State.stopped)){
				for(TextField one : array) if(one!=null) one.setId("completed");
			}
			else{
				for(TextField one : array) if(one!=null) one.setId("nothing");
			}
			setGraphic(content);
		}
		else{
			setGraphic(null);
		}
	}
}
