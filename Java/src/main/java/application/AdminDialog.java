package application;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.sql.SQLException;
import java.util.UUID;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import HW.iButton;
import javafx.scene.control.ButtonBar.ButtonData;

/*
 * Dialog for adding new user 
 */

public class AdminDialog extends AddDialog{ 
	private iButton bt = new iButton();
	
	public AdminDialog(){
		do{
			//needed because of dialogbox has as parent main window and won't
			//display on top of current dialog
			frame.setAlwaysOnTop(true); 
			run();
		}while(!Exit&&
				DialogBoxes.ConfBox("Do you want add another user ? \n", "Admin mode").get().getButtonData()==ButtonData.OK_DONE);
		
		frame.requestFocus();
		close();
	}
	
	private void run(){
		String id=UUID.randomUUID().toString();
		String name="";
		int step=0;
		
		while(step!=1){
			if(step==0){
				name=getName();
				
				if(Exit){
					close();
					return;
				}
				else {step++;Enter=false;}
			}
		}
		
		User user = new User(UUID.randomUUID().toString(),name,id);
		
		frame.setAlwaysOnTop(false);
		try {
			db.saveUser(user);
			DialogBoxes.InfoBox("New user was succesfully added"+name);
		} catch (SQLException e) {
			DialogBoxes.ErrorBox("Error occured while connecting to database");
		}
	}
	
	private String loadId(){
		setUpFirst();
		update();
		//to be sure keyEvent will work properly
		frame.requestFocus();
		
		instruction.setText("Attach an ibutton");
		code.setText("0");
		
		String id = bt.readID();
		
		while(id==null&&!Exit){
			id=bt.readID();
		}
		
		code.setText(id);
		
		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			Log.StackTrace(e);
			Log.ErrorLog("interrup error see StactTrace log");
		}
		
		return id;
	}
	
	private String getName(){
		JPanel panel3 = new JPanel();
		
		GridBagLayout grid = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		panel3.setLayout(grid);
		
		JLabel instruction = new JLabel("Type user name");
		JTextField input = new JTextField();
		
		int hgap = frame.getWidth()/2;
		int vgap = frame.getHeight()/16;
		
		addManager(0,0,GridBagConstraints.HORIZONTAL,instruction,c,panel3,new Insets(vgap,hgap,vgap,hgap),30,KeyListen_o);
		addManager(0,1,GridBagConstraints.HORIZONTAL,input,c,panel3,new Insets(vgap,hgap,vgap,hgap),20,KeyListen_o);
		
		frame.setContentPane(panel3);
		update();
		input.requestFocus();
		
		while(!Exit){
			while(!Enter&&!Exit){
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					Log.StackTrace(e);
					Log.ErrorLog("interrupt error see StactTrace log");
				}
			}
			
			if(!Exit){
				Enter=false;
				return input.getText();
			}
		}
		return null;
	}
}
