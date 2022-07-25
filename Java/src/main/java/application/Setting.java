package application;

import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

import DBwrapper.Database_obj;

//class for loading threads list 
public class Setting {
	
	private enum db_types{
		THREADS
	}
	
	private Map<db_types,String> type2str = new HashMap<db_types,String>();
	
	private Database_obj db;
	
	public Setting(){
		db=new Database_obj();
		
		type2str.put(db_types.THREADS,"conf_threads_list");
	}
	
	public String[] getListOfThreads(){
		String result=null;
		
		try {
			result = db.confLoad(type2str.get(db_types.THREADS));
		} catch (SQLException e) {
			Log.StackTrace(e);
			Log.WarningLog("Error occured while connecting to database see StackTrace: Settings");
			System.exit(0);
		}
		
		return result.split(";");
	}
}
