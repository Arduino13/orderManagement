package application;

import java.util.Arrays;
import java.util.Optional;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.geometry.Insets;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonBar.ButtonData;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Dialog;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.control.TextInputDialog;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyCodeCombination;
import javafx.scene.input.KeyCombination;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.GridPane;
import javafx.util.Pair;
import javafx.scene.control.Button;

public final class DialogBoxes {
	
	public static String window = "Pre-alpha 0.1";
	//prevets displaying multiple message boxes
	private static boolean on_top = false; 
	private static KeyCombination keyComb_o = new KeyCodeCombination(KeyCode.O,KeyCombination.CONTROL_DOWN);
	private static KeyCombination keyComb_c = new KeyCodeCombination(KeyCode.C,KeyCombination.CONTROL_DOWN);
	
	public static void InfoBox(String text){
		if(!on_top){
			Alert alert = new Alert(AlertType.INFORMATION);
			alert.setTitle(window);
			alert.setHeaderText(null);
			alert.setContentText(text);
		
			on_top = true;
		
			alert.showAndWait();
		
			on_top = false;
			Log.InfoLog(text);
		}
	}
	
	public static void ErrorBox(String text){
		if(!on_top){
			Alert alert = new Alert(AlertType.ERROR);
			alert.setTitle(window);
			alert.setHeaderText(null);
			alert.setContentText(text);
			
			on_top=true;
			
			alert.showAndWait();
		
			on_top=false;
			Log.ErrorLog(text);
		}
	}
	
	//yes or no dialog
	public static Optional<ButtonType> ConfBox(String text,String header){
		Dialog <ButtonType> dialog = new Dialog<>();
		dialog.setTitle(window);
		dialog.setHeaderText(header);
		
		ButtonType confButtonType = new ButtonType("Yes",ButtonData.OK_DONE);
		ButtonType cancelButtonType = new ButtonType("No",ButtonData.CANCEL_CLOSE);
		
		dialog.setGraphic(new ImageView(FxmlControl.class.getResource("/info.png").toString()));
		dialog.getDialogPane().getButtonTypes().addAll(confButtonType, cancelButtonType);
		dialog.getDialogPane().setOnKeyTyped(e->{
			if(e.getCharacter().equals("n")){
				((Button)dialog.getDialogPane().lookupButton(cancelButtonType)).fire();
			}
			if(e.getCharacter().equals("y")){
				((Button)dialog.getDialogPane().lookupButton(confButtonType)).fire();
			}
		});
		
		Label label = new Label(text);
		dialog.getDialogPane().setContent(label);
	
		return dialog.showAndWait();
	}
	
	//small dialog with combo box for state select
	public static Optional<String> ItemChDialog(){
		Dialog<String> dialog = new Dialog<>();
		dialog.setTitle(window);
		dialog.setHeaderText("Chaning order state");
		
		ButtonType confButtonType = new ButtonType("Ok",ButtonData.OK_DONE);
		ButtonType cancelButtonType = new ButtonType("Close",ButtonData.CANCEL_CLOSE);
		dialog.getDialogPane().getButtonTypes().addAll(confButtonType, cancelButtonType);
		dialog.setGraphic(new ImageView(FxmlControl.class.getResource("/info.png").toString()));
		
		ComboBox<String> comboBox = new ComboBox<String>(FXCollections.observableArrayList(Arrays.asList(State.choises)));
		comboBox.setOnKeyPressed(e ->{
			if(keyComb_c.match(e)){
				System.out.println("match");
				dialog.close();
			}
		});
		comboBox.setOnKeyTyped(e ->{
			boolean isNumber=false;

			try{//e.getCode().isDigit() doesn't work
				Integer.parseInt(e.getCharacter()); 
				isNumber=true;
			}catch(NumberFormatException error){
				System.out.println("No number was entered");
			}
			
			if(isNumber){
				if(Integer.parseInt(e.getCharacter())>0&&Integer.parseInt(e.getCharacter())<State.choises.length){
					comboBox.setValue(State.choises[Integer.parseInt(e.getCharacter())]);
				}
				else{
					comboBox.setValue(State.choises[0]);
				}
			}
		});
		comboBox.setValue(State.choises[0]);
		dialog.getDialogPane().setContent(comboBox);
		
		Platform.runLater(() -> comboBox.requestFocus());
		
		dialog.setResultConverter(dialogButton -> {
			if(dialogButton == confButtonType){
				return comboBox.getValue();
			}
			return null;
		});
		
		return dialog.showAndWait();
	
	}
	
	//dialog prompt when control is interrupted
	public static Optional<String> ReasonDialog(){
		TextInputDialog dialog = new TextInputDialog();
		dialog.setTitle("Control interruption");
		dialog.setHeaderText(null);
		dialog.setContentText("Reason:");
		
		dialog.getDialogPane().getButtonTypes().clear();
		ButtonType loginButtonType = new ButtonType("OK", ButtonData.OK_DONE);
		ButtonType cancelButtonType = new ButtonType("Close", ButtonData.CANCEL_CLOSE);
		dialog.getDialogPane().getButtonTypes().addAll(loginButtonType, cancelButtonType);
		
		((TextField)dialog.getDialogPane().lookup(".text-field")).setOnKeyPressed(e->{
			if(keyComb_c.match(e)){
				((Button)dialog.getDialogPane().lookupButton(cancelButtonType)).fire();
			}
			if(keyComb_o.match(e)){
				((Button)dialog.getDialogPane().lookupButton(loginButtonType)).fire();
			}
		});
		
		return dialog.showAndWait();
	}
	
	//Dialog which prompt user to enter number of controlled pieces
	public static Optional<String> NumberDialog(){
		TextInputDialog dialog = new TextInputDialog();
		dialog.setTitle("Number of controlled pieces");
		dialog.setHeaderText(null);
		dialog.setContentText("Number of controlled pieces:");
		
		dialog.getDialogPane().getButtonTypes().clear();
		ButtonType loginButtonType = new ButtonType("OK", ButtonData.OK_DONE);
		ButtonType cancelButtonType = new ButtonType("Close", ButtonData.CANCEL_CLOSE);
		dialog.getDialogPane().getButtonTypes().addAll(loginButtonType, cancelButtonType);
		
		((TextField)dialog.getDialogPane().lookup(".text-field")).setOnKeyPressed(e->{
			if(keyComb_c.match(e)){
				((Button)dialog.getDialogPane().lookupButton(cancelButtonType)).fire();
			}
			if(keyComb_o.match(e)){
				((Button)dialog.getDialogPane().lookupButton(loginButtonType)).fire();
			}
		});
		
		dialog.setResultConverter(dialogButton -> {
			boolean numeric = true;
			
			try{
				Integer.parseInt(((TextField)dialog.getDialogPane().lookup(".text-field")).getText());
			}catch (NumberFormatException | NullPointerException nfe){
				numeric=false;
			}
			
			if (dialogButton == loginButtonType&&numeric) {
				return ((TextField)dialog.getDialogPane().lookup(".text-field")).getText();
			}
			else if(dialogButton == loginButtonType&&!numeric){
				ErrorBox("Enter number");
			}
			return null;
		});
		
		return dialog.showAndWait();
	}

	public static Optional<Pair<String,String>> InputDialog(){
		if(!on_top){
			Dialog<Pair<String, String>> dialog = new Dialog<>();
			dialog.setTitle("Admininistrator mode");
			dialog.setHeaderText("Fill in login credentials");
	
			dialog.setGraphic(new ImageView(FxmlControl.class.getResource("/info.png").toString()));

			ButtonType loginButtonType = new ButtonType("OK", ButtonData.OK_DONE);
			ButtonType cancelButtonType = new ButtonType("Close", ButtonData.CANCEL_CLOSE);
			dialog.getDialogPane().getButtonTypes().addAll(loginButtonType, cancelButtonType);

			GridPane grid = new GridPane();
			grid.setHgap(10);
			grid.setVgap(10);
			grid.setPadding(new Insets(20, 150, 10, 10));

			TextField username = new TextField();
			username.setPromptText("User name");
			PasswordField password = new PasswordField();
			password.setPromptText("Password");
		
			class helper_input{
				void helperF(KeyEvent e){
					if(keyComb_c.match(e)){
						((Button)dialog.getDialogPane().lookupButton(cancelButtonType)).fire();
					}
					if(keyComb_o.match(e)){
						((Button)dialog.getDialogPane().lookupButton(loginButtonType)).fire();
					}
					if(e.getCode().equals(KeyCode.UP)){
						Platform.runLater(()->username.requestFocus());
					}
					if(e.getCode().equals(KeyCode.DOWN)){
						Platform.runLater(()->password.requestFocus());
					}
				}
			}
		
			username.setOnKeyPressed(e->new helper_input().helperF(e));
			password.setOnKeyPressed(e->new helper_input().helperF(e));
			
			//fast patch because administrator was only one 
			username.setText("root"); 

			grid.add(new Label("User name"), 0, 0);
			grid.add(username, 1, 0);
			grid.add(new Label("Password:"), 0, 1);
			grid.add(password, 1, 1);

			dialog.getDialogPane().setContent(grid);

			Platform.runLater(() -> username.requestFocus());

			dialog.setResultConverter(dialogButton -> {
				if (dialogButton == loginButtonType) {
					return new Pair<>(username.getText(), password.getText());
				}
				return null;
			});

			on_top=true;
			Optional<Pair<String,String>> result = dialog.showAndWait();
			on_top=false;
			return result;
		}
		return null;
	}
}
