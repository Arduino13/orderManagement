package application;

import java.util.Arrays;
import java.util.Date;

//Class that represents control of an manufactured item

public class Control extends Item {
	public enum COUNT{
		FIRST,
		SECOND,
		UNKNOWN
	}
	
	public static String[] str = {"Prvn�","Druh�"};
	private static COUNT[] c2str = {COUNT.FIRST,COUNT.SECOND};
	
	private COUNT count=COUNT.UNKNOWN;
	private String reason="";
	
	public Control(String id, String batch, String number, User u, COUNT count, Date from){
		super(from,null,id,u,batch,number);
		this.count=count;
	}
	
	public void setCount(COUNT c){
		count=c;
	}
	
	public void setReason(String s){
		reason=s;
	}
	
	public COUNT getCount(){
		return count;
	}
	
	public String getReason(){
		return reason;
	}
	
	public static COUNT str2count(String s){
		if(Arrays.asList(str).indexOf(s)!=-1) return COUNT.values()[Arrays.asList(str).indexOf(s)];
		else return null;
	}
	
	public static String count2str(COUNT count){
		int index = Arrays.asList(c2str).indexOf(count);
		
		if(index!=-1) return str[index];
		else return null;
	}
}
