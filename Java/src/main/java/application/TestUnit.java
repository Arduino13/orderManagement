package application;


import java.sql.SQLException;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.Date;
import org.junit.*;
import static org.junit.Assert.*;

import DBwrapper.Database_obj;

public class TestUnit {
	private Database_obj db;
	private Date now = Date.from(LocalDate.now()
			  .atStartOfDay()
		      .atZone(ZoneId.systemDefault())
		      .toInstant());
	private User user = new User("h","pepa","23232");
	
	private Item item = new Item(now,new State(State.inProgress),"h",user,"23","3434");
	
	//private String UUID = java.util.UUID.randomUUID().toString();
	
	
   @Before
   public void setUP(){
	   db = new Database_obj();
   }
   
   @Test
   public void DatabaseTest() throws SQLException{
	 for(int i=0;i<2;i++){ //test of new and update
	   assertEquals(1,db.saveUser(user),0);
	   assertEquals(1,db.saveItem(item),0);
	 }
	   db.loadUser("h");
	   db.loadListUser();
	   
	   db.loadItem("h");
	   db.loadListItem();
	   
	   db.confSave("conf_test","testing");
	   db.confSave("conf_test","testing2");
	   
	   item.setScrew("ahoj", null, "M3", Item.Screw.screw_t.LEFT);
	   
	   for(int i=0;i<2;i++){
		   assertEquals(1,db.saveItem(item),0);
	   }
	   
	   db.loadItem("h");
	   
	   assertEquals(1,db.deleteConf("conf_test"),0);
	   assertEquals(1,db.deleteScrew("ahoj"),0);
	   assertEquals(1,db.deleteUser(user),0);
	   assertEquals(1,db.deleteItem(item),0);
   }
   
   @Test
   public void RecordTest() throws SQLException{
	   assertEquals(1,db.saveRecord(item),0);
	   assertEquals(1,db.deleteHistory(),0);
   }
   
   @Test(expected=IllegalArgumentException.class)
   public void ExceptionsDB() throws SQLException{
	   Item item_n = item;
	   User user_n = user;
	   item_n.setDateFrom(null);
	   user_n.setId(null);
	   db.saveItem(item_n);
	   db.saveUser(user_n);
	   db.loadItem("dfdfdf");
	   db.loadUser("dfdfdfdfdfdf");
   }
}