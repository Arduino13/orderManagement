package HW;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import application.DialogBoxes;
import application.Log;

//class for reading from barcode scanner, runs in its own thread

public class BarCodeReader implements Runnable{
	//arrays to convert from barcode code to ascii
	private char lowerA[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
	           'n','o','p','q','r','s','t','u','v','w','x','y',
	           'z','1','2','3','4','5','6','7','8','9','0',' ',
	           '-','=','[',']','\\',';','\'','~', ',','.','/'};
	private char ShiftA[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
            'N','O','P','Q','R','S','T','U','V','W','X','Y',
            'Z','!','@','#','$','%','^','&','*','(',')',' ',
            '_','+','{','}','|',':','"','~','<','>','?'};
	
	private Map<Integer,String> lower = new HashMap<>();
	private Map<Integer,String> Shift = new HashMap<>();
	
	public String result="";
	
	public BarCodeReader(){
		int offset=4;
		for(int i=0;i<lowerA.length;i++){
			if(lowerA[i]==' ') offset+=5;
			if(lowerA[i]==':') offset+=2;
						
			lower.put(i+offset,Character.toString(lowerA[i]));
			Shift.put(i+offset,Character.toString(ShiftA[i]));
		}
	}
	
	@Override
	public void run(){
		try {
			result="";
			result=readString();
		} catch (IOException e) {
			DialogBoxes.ErrorBox("Barcode scanner is not connected");
			Log.StackTrace(e);
		}
	}
	
	public String readString() throws IOException{	
		ArrayList<Integer> code = readCode();
		String result="";
		boolean shift=false;
		int shift_c=0;
		
		for(int i=0;i<code.size();i++){
			int Char = code.get(i);
			
			if(Char==2){ //enabling shift 
				shift_c++;
				if(shift_c>=2){
					shift=true;
					shift_c=0;
				}
			}
			else if(shift){
				result+=Shift.get(Char);
				shift=false;
			}
			else{
				result+=lower.get(Char);
			}
		}
		return result;
	}
	public int readNumber() throws IOException{
		ArrayList<Integer> code = readCode();
		int result=0;
		for(int i=0;i<code.size();i++){
			if(i==0) result=code.get(0);
			else{
				result+=code.get(i)*10*i;
			}
		}
		return result;
	}
	
	private ArrayList<Integer> readCode() throws IOException{
			FileReader reader = new FileReader("/dev/hidraw0");
			ArrayList<Integer> list = new ArrayList<>();
			
			while(true){
					int Char = reader.read();
					if(Char>0){
						if(Char==40){ //charachter marking the end
							break;
						}
						else{
							list.add(Char);
						}
					}
			}
			
			reader.close();
			return list;
	}

}
