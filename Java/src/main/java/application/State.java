package application;

import java.util.Arrays;

//representation of item's state
public class State implements Comparable<State>{
	public final static int inProgress = 0;
	public final static int stopped = 2;
	public final static int paused = 1;
	public final static int completed = 3;
	public final static int unknown = 4;
	
	public static final String choises[] = {"done","in progress","stopped","paused"};
	private static final int choises_i[] = {completed,inProgress,stopped,paused}; //jista primitvni mapa 
	
	private int state=unknown;
	
	public State(int state){
		this.state=state;
	}
	
	@Override 
	public String toString(){
		switch(state){
			case inProgress:
				return "in progress";
			case stopped:
				return "stopped";
			case paused:
				return "paused";
			case completed:
				return "done";
		}
		return "unknown";
	}
	
	public State setState(int value){
		state=value;
		return this;
	}
	public int getState(){
		return state;
	}
	
	public static int str2State(String str){
		if(Arrays.asList(choises).indexOf(str)!=-1){
			return choises_i[Arrays.asList(choises).indexOf(str)];
		}
		else{
			return unknown;
		}
	}
	
	//use to sort items in table by state
	@Override
	public int compareTo(State second){
		final int EQUAL = 0;
		final int BEFORE = -1;
		final int AFTER = 1;
		
		if(state==second.getState()) return EQUAL;
		else if(second.getState()==completed) return BEFORE;
		else if(state < second.getState()) return BEFORE;
		else if(state > second.getState()) return AFTER;
		
		return EQUAL;
	} 
}
