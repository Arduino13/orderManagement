package application;


import HW.BarCodeReader;

//wrapper around BarCodeReader class 

public class BarCode {
	
	public BarCodeReader reader = new BarCodeReader();

	//loads text that coresponds to batch number
	public String loadBatch(){
		String text = loadText();
		//if(text.contains("S")) return text;
		if(!text.isEmpty()) return text;
		else return null;
	}

	//loads text that coresponds to drawing number
	public String loadNumber(){
		String text = loadText();
		//if(text.contains("P")) return text.substring(1);
		if(!text.isEmpty()) return text;
		else return null;
	}

	//loads any text
	public String loadText(){
		Thread t1 = new Thread(reader);
		try{
			t1.start();
			
			Thread.sleep(100);
			
			return reader.result;
			
		} catch (Exception e) {
			DialogBoxes.ErrorBox("Barcode reader is not connected");
			Log.StackTrace(e);
			return null;
		}
		finally{
			t1.interrupt();
		}
	}
}
