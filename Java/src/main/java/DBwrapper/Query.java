package DBwrapper;

//pust together string SQL command

public class Query {
	private StringBuilder query;
	
	public Query delete(String table){
		query = new StringBuilder();
		query.append("DELETE FROM ");
		query.append(table);
		return this;
	}
	
	public Query where(String requirement){
		query.append(" WHERE ");
		query.append(requirement);
		return this;
	}
	
	public Query update(String table){
		query = new StringBuilder();
		query.append("UPDATE ");
		query.append(table);
		query.append(" SET ");
		return this;
	}
	
	public Query set(String[] columns){
		int count = columns.length;
		if(count == 0)
			throw new IllegalArgumentException("Parametrs cant be 0");
		
		for(String colum : columns){
			query.append(colum);
			query.append(" = ");
			query.append("?");
			query.append(",");
		}
		query.deleteCharAt(query.lastIndexOf(","));
		return this;
	}
	
    public Query insert(String table){
        query = new StringBuilder();
        query.append("INSERT INTO ");
        query.append(table);
        return this;
    }
    
    public Query values(Object[] params){
        query.append(" VALUES(");

        int count = params.length;

        if(count == 0)
            throw new IllegalArgumentException("Neplatn� po�et parametr�");

        for (int i = 0; i<count; i++) {
            query.append("?,");
        }
        query.deleteCharAt(query.lastIndexOf(","));
        query.append(");");
        return this;
    }
    
    public Query select(Object[] columns){
        query = new StringBuilder();
        query.append("SELECT ");
        if(columns != null){
            for(Object column : columns){
                query.append(column);
                query.append(",");
            }
            query.deleteCharAt(query.lastIndexOf(","));
        }
        else
            query.append("*");

        return this;
    }
    
    public Query from(String table){
    	query.append(" FROM ");
    	query.append(table);
    	return this;
    }
    
    public String getQuery(){
        return query.toString();
    }
    
    
}
