package DBwrapper;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import application.Item;
import application.Control;
import application.Item.Screw;
import application.User;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import application.State;

import static application.Item.Screw.screw_t; 

/*
 * Handles saving, loading and deleting of application objects
 */

public class Database_obj {
	
	private String name_db = "DB NAME";
	public String name = "USER NAME";
	public String pass = "DB PASSWORD";
	
	private enum type{
		USER,
		RECORD,
		HISTORY_R,
		CONF,
		SCREW,
		CONTROL,
		HISTORY_C
	}
	
	private Map<type,String> type2str = new HashMap<type,String>();
	
	public Database_obj(){
		type2str.put(type.USER, "users");
		type2str.put(type.RECORD, "records");
		type2str.put(type.HISTORY_R,"history_rec");
		type2str.put(type.CONF, "setting");
		type2str.put(type.SCREW, "items");
		type2str.put(type.CONTROL, "controls");
		type2str.put(type.HISTORY_C, "history_con");
	}
	
	private Database open() throws SQLException{
		return new Database(name_db,name,pass);
	}
	
	private boolean TestIt(ResultSet rs) throws SQLException{
		if(rs.next() == false) return false;
		else return true;
	}
	
	public boolean exist(Control con, State st) throws SQLException{
		Database db=open();
		Object[] colum = {"*"};
		Object[] id_o = {con.getBatch(),con.getNumber(),st.getState()};
		
		ResultSet rs = db.select(type2str.get(type.CONTROL),colum,"batch = ? AND number = ? AND state = ?",id_o);
		boolean to_return = TestIt(rs);
		return to_return;
	}
	
	public boolean exist(Control con) throws SQLException{
		Database db=open();
		Object[] colum = {"*"};
		Object[] id_o = {con.getBatch(),con.getNumber()};
		
		ResultSet rs = db.select(type2str.get(type.CONTROL),colum,"batch = ? AND number = ?",id_o);
		boolean to_return = TestIt(rs);
		return to_return;
	}
	
	@Deprecated 
	public boolean exist(Item item) throws SQLException{
		return false;
	}
	
	private boolean exist(type typ, String id) throws SQLException{
		Database db=open();
		Object[] colum = {"*"};
		Object[] id_o = {id};
		
		switch(typ){
			case USER:
				ResultSet rs = db.select(type2str.get(type.USER),colum,"id = ?",id_o);
				boolean to_return = TestIt(rs);
				return to_return;
			case RECORD:
				ResultSet rs1 = db.select(type2str.get(type.RECORD),colum, "id = ?", id_o);
				boolean to_return1 = TestIt(rs1);
				return to_return1;
			case HISTORY_R:
				ResultSet rs2 = db.select(type2str.get(type.HISTORY_R),colum, "id = ?", id_o);
				boolean to_return2 = TestIt(rs2);
				return to_return2;
			case CONF:
				ResultSet rs3 = db.select(type2str.get(type.CONF),colum, "id = ?", id_o);
				boolean to_return3 = TestIt(rs3);
				return to_return3;
			case SCREW:
				ResultSet rs4 = db.select(type2str.get(type.SCREW),colum, "id = ?", id_o);
				boolean to_return4 = TestIt(rs4);
				return to_return4;
			case CONTROL:
				ResultSet rs5 = db.select(type2str.get(type.CONTROL),colum, "id = ?", id_o);
				boolean to_return5 = TestIt(rs5);
				return to_return5;
			case HISTORY_C:
				ResultSet rs6 = db.select(type2str.get(type.HISTORY_C),colum, "id = ?", id_o);
				boolean to_return6 = TestIt(rs6);
				return to_return6;
		}
		db.close();
		return false;
	}
	
	public int saveItem(Item to_save) throws SQLException,IllegalArgumentException{
		Database db = open();
		boolean New = !exist(type.RECORD,to_save.getID());
		
		String screwId = to_save.getScrew()==null ? null : to_save.getScrew().getId();
		
		if(to_save.getDateFrom()==null||to_save.getState()==null||to_save.getUser()==null||to_save.getID()==null)
			throw new IllegalArgumentException("Object is inconsistent");
		
		if(screwId!=null) threadSave(to_save.getScrew()); 
		
		if(New){
			Object[] params = {to_save.getID(),to_save.getDateFrom(),to_save.getDateTo(),to_save.getUser().getId(),
					to_save.getState().getState(),to_save.getBatch(),to_save.getNumber(),screwId,to_save.getNumberOf()};
			int to_return = db.insert(type2str.get(type.RECORD),params);
			db.close();
			return to_return;
		}
		else{
			String[] columns = {"date_from","date_to","user_id","state","batch","number","screw","number_of"};
			Object[] params = {to_save.getDateFrom(),to_save.getDateTo(),to_save.getUser().getId(),to_save.getState().getState(),
					to_save.getBatch(),to_save.getNumber(),screwId,to_save.getNumberOf(),to_save.getID()};
			int to_return = db.update(type2str.get(type.RECORD),columns,"id=?",params);
			db.close();
			return to_return;
		}
	}
	
	public int saveUser(User to_save) throws SQLException,IllegalArgumentException{
		Database db = open();
		boolean New = !exist(type.USER,to_save.getId());
		
		if(to_save.getCardNumber()==null||to_save.getName()==null||to_save.getId()==null)
			throw new IllegalArgumentException("Object is inconsistent");
		
		if(New){
			Object[] params = {to_save.getId(),to_save.getCardNumber(),to_save.getName(),to_save.getLast()};
			int to_return=db.insert(type2str.get(type.USER),params);
			db.close();
			return to_return;
		}
		else{
			String[] columns = {"card_number","name","last_updated"};
			Object[] params = {to_save.getCardNumber(),to_save.getName(),to_save.getLast(),to_save.getId()};
			int to_return = db.update(type2str.get(type.USER),columns,"id=?",params);
			db.close();
			return to_return;
		}
	}
	
	public int saveControl(Control control) throws SQLException,IllegalArgumentException{
		Database db = open();
		boolean New = !exist(type.CONTROL,control.getID());
		
		if(control.getDateFrom()==null||control.getState()==null||control.getUser()==null||control.getID()==null||control.getCount()==Control.COUNT.UNKNOWN)
			throw new IllegalArgumentException("Object is inconsistent");
		
		if(New){
			Object[] params = {control.getID(),control.getDateFrom(),control.getDateTo(),control.getUser().getId(),
					control.getState().getState(),control.getBatch(),control.getNumber(),control.getNumberOf(),control.getCount().name(),control.getReason()};
			int to_return = db.insert(type2str.get(type.CONTROL),params);
			db.close();
			return to_return;
		}
		else{
			Object[] params = {control.getDateFrom(),control.getDateTo(),control.getUser().getId(),control.getState().getState(),
					control.getBatch(),control.getNumber(),control.getNumberOf(),control.getCount().name(),control.getReason(),control.getID()};
			String[] columns = {"date_from","date_to","user_id","state","batch","number","number_of","count","reason"};
			int to_return = db.update(type2str.get(type.CONTROL),columns,"id=?",params);
			db.close();
			return to_return;
		}
	}
	public int saveControl_h(Control control) throws SQLException{
		return saveControl_h(control,false);
	}
	
	//not_now is to add delay to time, otherwise if multiple records (max 2) are saved,
	//they'll have same date a that'll cause problems with history records
	public int saveControl_h(Control control,boolean not_now) throws SQLException{
		Database db = open();
		Date now = Date.from(LocalDateTime.now()
			      .atZone(ZoneId.systemDefault())
			      .toInstant());
		if(not_now) now.setTime(now.getTime()+1000);
		Object[] param = {control.getID(),now,control.getUser().getId(),control.getState().getState()};
		
		int to_return = db.insert(type2str.get(type.HISTORY_C), param);
		db.close();
		
		return to_return;
	}
	
	public Control loadControl(String id) throws SQLException{
		Database db = open();
		Object[] obj = {"*"};
		Object[] target = {id};
		
		ResultSet rs =  db.select(type2str.get(type.CONTROL),obj,"id=?",target);
		
		if(!rs.next())
			throw new IllegalArgumentException("item does not exist");
		
		String id_item = rs.getString("id");
		Date date_from = new Date(rs.getTimestamp("date_from").getTime());
		Date date_to = rs.getDate("date_to");
		String userId = rs.getString("user_id");
		State state = new State(rs.getInt("state"));
		String batch = rs.getString("batch");
		String number = rs.getString("number");
		int numberOf = rs.getInt("number_of");
		Control.COUNT count = Control.COUNT.valueOf(rs.getString("count"));
		String reason = rs.getString("reason");
		
		Control New = new Control(id_item,batch,number,loadUser(userId),count,date_from);
		if(date_to!=null)
			New.setDateTo(new Date(rs.getTimestamp("date_to").getTime()));
		
		New.setNumberOf(numberOf);
		New.setState(state);
		New.setReason(reason);
		
		db.close();
		
		if(New.getUser()!=null) return New;
		else return null;
	}
	
	private User loadUser(String id,String req) throws SQLException,IllegalArgumentException{
		Database db = open();
		Object[] obj = {"*"};
		Object[] target = {id};
		
		ResultSet rs = db.select(type2str.get(type.USER),obj,req,target);
		
		if(!rs.next())
			throw new IllegalArgumentException("user does not exist");
		
		String id_user = rs.getString("id");
		String cardNumber = rs.getString("card_number");
		String name = rs.getString("name");
		String last = rs.getString("last_updated");
		
		db.close();
		
		User u = new User(id_user,name,cardNumber);
		if(last!=null) u.setLast(last);
		return u;
	}
	
	public User loadUser(String id) throws SQLException,IllegalArgumentException{
		return loadUser(id,"id=?");
	}
	public User loadUser_card(String card) throws SQLException,IllegalArgumentException{
		return loadUser(card,"card_number=?");
	}
	
	private ObservableList<Item> loadHistory(String id,type What) throws SQLException{
		Database db = open();
		Object[] obj = {"*"};
		Object[] target = {id};
		ObservableList<Item> to_return = FXCollections.observableArrayList();
		
		ResultSet rs = db.select(type2str.get(What), obj, "id=?", target);
		
		while(rs.next()){
			String id_item = id;
			Date date = new Date(rs.getTimestamp("date").getTime());
			User user = loadUser(rs.getString("user_id"));
			State state = new State(rs.getInt("state"));
			
			to_return.add(new Item(date,state,id_item,user,null,null));
		}
		
		return to_return;
	}
	
	public ObservableList<Item> loadHistory(String id) throws SQLException{
		return loadHistory(id,type.HISTORY_R);
	}
	
	public ObservableList<Control> loadHistory_c(String id) throws SQLException{
		ObservableList<Item> items = loadHistory(id,type.HISTORY_C);
		ObservableList<Control> controls = FXCollections.observableArrayList();
		for(Item i : items){
			controls.add(new Control(id,null,null,i.getUser(),Control.COUNT.FIRST,i.getDateFrom()));
		}
		
		return controls;
	}
	
	public Item loadItem(String id) throws SQLException,IllegalArgumentException{
		Database db = open();
		Object[] obj = {"*"};
		Object[] target = {id};
		
		ResultSet rs =  db.select(type2str.get(type.RECORD),obj,"id=?",target);
		
		if(!rs.next())
			throw new IllegalArgumentException("item does not exist");
		
		String id_item = rs.getString("id");
		Date date_from = new Date(rs.getTimestamp("date_from").getTime());
		Date date_to = rs.getDate("date_to");
		String userId = rs.getString("user_id");
		State state = new State(rs.getInt("state"));
		String batch = rs.getString("batch");
		String number = rs.getString("number");
		String screw = rs.getString("screw");
		int numberOf = rs.getInt("number_of");
		
		Item New = new Item(date_from,state,id_item,loadUser(userId),batch,number);
		if(date_to!=null)
			New.setDateTo(new Date(rs.getTimestamp("date_to").getTime()));
		
		if(screw!=null){
			Object[] param = {screw};

			ResultSet rs2=db.select(type2str.get(type.SCREW),obj,"id=?", param);
			rs2.next(); //protoze ukazatel je pred prvnim sloupcem 
			
			String left = rs2.getString("type_thread_l");
			String right = rs2.getString("type_thread_r");
			screw_t current;
			
			if(rs2.getString("current")==null) current=screw_t.UNKNOWN;
			else current = rs2.getString("current").equals("first") ? screw_t.LEFT : screw_t.RIGHT;
			
			New.setScrew(screw, left, right, current);
		}
		
		New.setNumberOf(numberOf);
		
		db.close();
		
		if(New.getUser()!=null) return New;
		else return null;
	}
	
	public ObservableList<Item> loadListItem() throws SQLException{
		Database db = open();
		Object[] obj = {"id"};
		ObservableList<Item> to_return = FXCollections.observableArrayList();
		
		ResultSet list = db.select(type2str.get(type.RECORD), obj, null);
		
		while(list.next()){
			to_return.add(loadItem(list.getString("id")));
		}
		
		db.close();
		return to_return;
	}
	
	public ObservableList<User> loadListUser() throws SQLException{
		Database db = open();
		Object[] obj = {"id"};
		ObservableList<User> to_return = FXCollections.observableArrayList();
		
		ResultSet list = db.select(type2str.get(type.USER), obj, null);
		
		while(list.next()){
			to_return.add(loadUser(list.getString("id")));
		}
		
		db.close();
		return to_return;
	}
	
	public ObservableList<Control> loadListControl() throws SQLException{
		Database db = open();
		Object[] obj = {"id"};
		ObservableList<Control> to_return = FXCollections.observableArrayList();
		
		ResultSet list = db.select(type2str.get(type.CONTROL), obj, null);
		
		while(list.next()){
			to_return.add(loadControl(list.getString("id")));
		}
		
		db.close();
		return to_return;
	}
	public int saveRecord(Item item) throws SQLException{
		return saveRecord(item,false);
	}
	public int saveRecord(Item item, boolean not_now) throws SQLException{
		Database db = open();
		Date now = Date.from(LocalDateTime.now()
			      .atZone(ZoneId.systemDefault())
			      .toInstant());
		if(not_now) now.setTime(now.getTime()+1000);
		Object[] param = {item.getID(),now,item.getUser().getId(),item.getState().getState()};
		
		int to_return = db.insert(type2str.get(type.HISTORY_R), param);
		db.close();
		
		return to_return;
	}
	
	public int deleteItem(Item item) throws SQLException{
		Database db = open();
		Object[] param = {item.getID()};
		
		int to_return = db.delete(type2str.get(type.RECORD),"id=?", param);
		db.close();
		
		return to_return;	
	}
	
	public int deleteUser(User user) throws SQLException{
		Database db = open();
		Object[] param = {user.getId()};
		
		int to_return = db.delete(type2str.get(type.USER),"id=?", param);
		db.close();
		
		return to_return;	
	}
	
	public int deleteHistory() throws SQLException{
		Database db = open();
		
		int to_return = db.delete(type2str.get(type.HISTORY_R),"",null);
		db.close();
		
		return to_return;
	}
	
	public String confLoad(String id) throws SQLException{
		Database db = open();
		
		Object[] params = {id};
		Object[] obj = {"*"};
		
		ResultSet rs = db.select(type2str.get(type.CONF),obj,"id=?", params);
		
		rs.next();
		String to_return = rs.getString("value");
		
		db.close();
		
		return to_return;
	}
	private int threadSave(Screw item) throws SQLException{
		String id = item.getId();
		String number = item.getNumber();
		String left = item.getT(screw_t.LEFT);
		String right = item.getT(screw_t.RIGHT);
		String current = item.getC()==screw_t.LEFT ? "first" : "second";
		
		if(item.getC()==screw_t.UNKNOWN) current=null;
		
		Database db = open();
		boolean New = !exist(type.SCREW,id);
		
		if(New){
			Object[] params = {id,number,left,right,current};
			int to_return=db.insert(type2str.get(type.SCREW),params);
			db.close();
			return to_return;
		}
		else{
			String[] columns = {"number","type_thread_l", "type_thread_r","current"};
			Object[] params = {number,left, right,current,id};
			int to_return = db.update(type2str.get(type.SCREW),columns,"id=?",params);
			db.close();
			return to_return;
		}
	}
	
	public String thread_by_number(int number,screw_t type_s) throws SQLException{
		Database db = open();
		
		Object[] params = {number};
		Object[] obj = {"*"};
		
		String to_return;
		
		ResultSet rs = db.select(type2str.get(type.SCREW),obj,"number=?",params);
		
		rs.next();
		if(type_s==screw_t.LEFT) to_return=rs.getString("type_thread_l");
		else to_return=rs.getString("type_thread_r");
		
		db.close();
		return to_return;
	}
	
	public int confSave(String id,String conf) throws SQLException{
		Database db = open();
		boolean New = !exist(type.CONF,id);
		
		if(New){
			Object[] params = {id,conf};
			int to_return=db.insert(type2str.get(type.CONF),params);
			db.close();
			return to_return;
		}
		else{
			String[] columns = {"value"};
			Object[] params = {conf,id};
			int to_return = db.update(type2str.get(type.CONF),columns,"id=?",params);
			db.close();
			return to_return;
		}
	}
	
	public int deleteConf(String id) throws SQLException{
		Database db = open();
		Object[] param = {id};
		
		int to_return = db.delete(type2str.get(type.CONF),"id=?", param);
		db.close();
		
		return to_return;	
	}
	
	public int deleteScrew(String number) throws SQLException{
		Database db = open();
		Object[] param = {number};
		
		int to_return = db.delete(type2str.get(type.SCREW),"id=?", param);
		db.close();
		
		return to_return;	
	}
}
