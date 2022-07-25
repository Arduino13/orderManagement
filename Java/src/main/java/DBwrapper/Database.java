package DBwrapper;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

/*
 * Handles basic database functions insert, update etc.
 */

public class Database {
    protected Connection connection;

    protected Query query;
    
    public Database(String db, String userName, String password) throws SQLException{

        connection = DriverManager.getConnection("jdbc:mysql://rpi.lan/"+db+"?serverTimezone=UTC", userName, password);
    }
    
    public void close() throws SQLException{
    	connection.close();
    }

    private int query(String query, Object[] params) throws SQLException{
        PreparedStatement ps = connection.prepareStatement(query);
        if (params != null){
          int index = 1;
          for(Object param : params){
        	ps.setObject(index, param);
            index++;
          }
        }
        return ps.executeUpdate();
   }
    
   public int delete(String table, String requirement, Object[] param) throws SQLException{
        query = new Query();
        if(requirement!="")
        		query.delete(table)
        		.where(requirement);
        else
        		query.delete(table);
        
        return query(query.getQuery(), param);
    }
   
   public int insert(String table, Object[] params) throws SQLException{
       query = new Query();
       query.insert(table)
            .values(params);
       return query(query.getQuery(), params);
   }
   
   public ResultSet select(String table, Object[] columns, Object[] params) throws SQLException{
       return this.select(table, columns, "", params);
   }
   
   //version with WHERE expression
   public ResultSet select(String table, Object[] columns, String requirement, Object[] params) throws SQLException{
       query = new Query();
       
       if(requirement!="")
    	   query.select(columns)
    	   		.from(table)
    	   		.where(requirement);
       else
    	   query.select(columns)
    	   		.from(table);

       PreparedStatement ps = connection.prepareStatement(query.getQuery());
       if(params != null){
           int index = 1;
           for(Object param : params){
        		ps.setObject(index, param);
           		index++;
           }
       }

       ResultSet rs = ps.executeQuery();
       return rs;
   }
   
   public int update(String table, String[] columns, String requirement, Object[] params) throws SQLException{
       query = new Query();

       query.update(table)
            .set(columns)
            .where(requirement);

       return query(query.getQuery(), params);
   }
}
