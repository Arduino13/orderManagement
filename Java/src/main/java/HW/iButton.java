package HW;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import application.DialogBoxes;
import application.Main;
import javafx.application.Platform;

public class iButton {
	
	public String readID(){
		try {
			BufferedReader reader = new BufferedReader(new FileReader("/sys/devices/w1_bus_master1/w1_master_slaves"));
			String ID = reader.readLine();
			reader.close();
			
			BufferedWriter writer = new BufferedWriter(new FileWriter("/sys/devices/w1_bus_master1/w1_master_remove"));
			if(!ID.contains("not found")){
				writer.write(ID);
			}
			writer.close();
			
			if(!ID.contains("not found")){
				System.out.println(ID);
				return ID;
			}
			else return null;
			
		} catch (IOException e) {
			if(!Main.test) Platform.runLater(()->DialogBoxes.ErrorBox("Error occurred while trying to read from iButton device\n"+e.toString())); 
			return null;
		}
	}
	
}
