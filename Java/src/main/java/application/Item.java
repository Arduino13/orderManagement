package application;

import java.text.SimpleDateFormat;
import java.util.Comparator;
import java.util.Date;

//represents an order and is parent to Control class

public class Item{
	private Date dateFrom;
	private Date dateTo=null;
	private State state;
	private String id;
	private User user;
	private String batch;
	private String number;
	private Screw screw=null;
	private int numberOf=0;
	
	private interface enum_type{
		public enum screw_t{
			LEFT,
			RIGHT,
			UNKNOWN
		}
	}
	
	//innner class representing threads types and currently rolled thread
	public class Screw implements enum_type{
		private String id;
		private String left_t="";
		private String right_t="";
		private String number_s = number;
		private screw_t current=screw_t.UNKNOWN;
		
		public Screw(String id, String left, String right, screw_t current){
			this.id=id;
			left_t=left;
			right_t=right;
			this.current=current;
		}
		
		public Screw(String id, String left, String right){
			this.id=id;
			left_t=left;
			right_t=right;
		}
		
		public String getId(){
			return id;
		}
		
		public String getNumber(){
			return number_s;
		}
		
		public void setC(screw_t current){
			this.current=current;
		}
		
		public screw_t getC(){
			return current;
		}
		
		public String getT(screw_t type){
			return type==screw_t.LEFT ? left_t : right_t;
		}
	}
	
	//class for comparsion to sort items inside table
	public static class Compare implements Comparator<Item>{
		public enum type{
			DATE,
			STATE,
			ID
		}
		
		private type what=type.DATE;
		
		public Compare(type what){
			this.what=what;
		}
		
		@Override
		public int compare(Item first, Item second){
			switch(what){
				case DATE:
					return second.getDateFrom().compareTo(first.getDateFrom());
				case STATE:
					return first.getState().compareTo(second.getState());
				case ID:
					return first.getID().compareTo(second.getID());
			}
			return 0;
		}
	}
	
	public Item(Date date,State state,String id, User user, String batch, String number){
		this.dateFrom=date;
		this.state=state;
		this.id=id;
		this.user=user;
		this.batch=batch;
		this.number=number;
	}
	
	public Item setScrew(String id, String left, String right, Screw.screw_t current){
		if(left!=null||right!=null) screw=new Screw(id,left,right,current);
		return this;
	}
	
	public Item setScrew(String id,String left, String right){
		if(left!=null||right!=null) screw=new Screw(id,left,right);
		return this;
	}
	
	public Item setDateFrom(Date date){
		this.dateFrom=date;
		return this;
	}
	public Item setDateTo(Date date){
		this.dateTo=date;
		return this;
	}
	public Item setState(State state){
		this.state=state;
		return this;
	}
	public Item setID(String ID){
		id=ID;
		return this;
	}
	public Item setUserID(User ID){
		user=ID;
		return this;
	}
	public Item setBatch(String batch){
		this.batch=batch;
		return this;
	}
	public Item setNumber(String number){
		this.number=number;
		return this;
	}
	public Item setNumberOf(int numberOf){
		this.numberOf=numberOf;
		return this;
	}
	
	public Date getDateFrom(){
		return dateFrom;
	}
	public Date getDateTo(){
		return dateTo;
	}
	public String getDateFromS(){
		return new SimpleDateFormat("yyyy-MM-dd").format(dateFrom);
	}
	public String getDateToS(){
		return new SimpleDateFormat("yyyy-MM-dd").format(dateTo);
	}
	public State getState(){
		return state;
	}
	public String getID(){
		return id;
	}
	public User getUser(){
		return  user;
	}
	public String getBatch(){
		return batch;
	}
	public String getNumber(){
		return number;
	}
	public Screw getScrew(){
		return screw;
	}
	public int getNumberOf(){
		return numberOf;
	}

}
