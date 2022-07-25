package application;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public final class Log {
	
	private static void write_to_f(String f_name, String text){
		new File(System.getProperty("java.io.tmpdir")+"/"+DialogBoxes.window).mkdir();
		
		try{
			BufferedWriter fw = new BufferedWriter(new FileWriter("/var/log"+"/"+DialogBoxes.window+"/"+f_name,true));
			String now = LocalDateTime.now().format(DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm"));
			fw.newLine();
			fw.write(now+": "+text);
			fw.close();
		}catch(Exception e){
			System.out.println("behem zapisovani se vyskytla chyba");
			e.printStackTrace();
		}
	}
	
	public static void InfoLog(String message){
		System.out.println(message);
		write_to_f("info.log",message);
	}
	
	public static void ErrorLog(String message){
		System.out.println(message);
		write_to_f("error.log",message);
	}
	
	public static void WarningLog(String message){
		System.out.println(message);
		write_to_f("warning.log",message);
	}
	
	public static void StackTrace(Exception e){
		System.out.println(e);
		write_to_f("stack_trace.log",e.toString());
		write_to_f("stack_trace.log","-------------------------");
	}
}
