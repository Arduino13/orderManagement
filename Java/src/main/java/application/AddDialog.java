package application;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import javax.swing.*;

import DBwrapper.Database_obj;
import javafx.scene.control.ButtonBar.ButtonData;

/*
 * Dialog for creating new order
 *
 * Together with AdminDialog which inherits from this class, these are only
 * two dialogs that use older Java Swing library
 */

public class AddDialog {
	
	Database_obj db = new Database_obj();
	
	JLabel instruction = new JLabel();
	JLabel code = new JLabel();
	
	JFrame frame = new JFrame("");

	//variables that 'holds' key press on specific keys
	boolean BackSpace = false;
	boolean Exit = false;
	boolean Enter = false;
	KeyListen KeyListen_o = new KeyListen();
	
	//inits window layout
	void setUpFirst(){
		JPanel panel1 = new JPanel();
		
		GridLayout grid = new GridLayout(2,0);
		grid.setVgap(20);
		panel1.setLayout(grid);
		
		for(JLabel t : array){
			t.setHorizontalAlignment(JLabel.CENTER);
			t.setFont(new Font(t.getFont().getName(),Font.PLAIN,40));
			panel1.add(t);
		}
		
		frame.setContentPane(panel1);
	}
	
	//redraws window
	void update(){
		frame.invalidate();
		frame.validate();
		frame.repaint();
	}
	
	void close(){
		frame.setVisible(false);
	}
// End of section that is common for AdminDialog and AddDialog
//---------------------------------------------			
			
	private BarCode reader = new BarCode();
	private User user;
	
	private Map<Item.Screw.screw_t,String> type2str = new HashMap<Item.Screw.screw_t,String>();
	
	private JLabel array[]={instruction,code};
	
	private enum choose_e{
		CONTROL,
		ROLLING,
		NOTHING
	}
	
	private Item id_new=null;
	
	//variables that holds selected mode
	private boolean control_pressed=false;
	private boolean rolling_pressed=false;
	
	private class KeyListen implements KeyListener{
		@Override
		public void keyPressed(KeyEvent e) {
			if(e.getKeyChar()==KeyEvent.VK_ENTER) Enter=true; 
		}

		@Override
		public void keyReleased(KeyEvent e) {
		}

		@Override
		public void keyTyped(KeyEvent e) {
			if(e.getKeyChar()==KeyEvent.VK_BACK_SPACE) BackSpace=true;
		}
	}
	
	//connects key listener
	private void init(){
		setUpFirst();
		
		frame.setExtendedState( frame.getExtendedState()|JFrame.MAXIMIZED_BOTH );
		frame.addKeyListener(KeyListen_o);
		
		frame.addWindowListener(new java.awt.event.WindowAdapter() {
		    @Override
		    public void windowClosing(java.awt.event.WindowEvent windowEvent) {
		    	Exit=true;
		    }
		});
		
		frame.setVisible(true);
	}
	
	public AddDialog(){ //constructor for AdminDialog 
		init();
	}
	
	public AddDialog(User user){
		type2str.put(Item.Screw.screw_t.LEFT, "First");
		type2str.put(Item.Screw.screw_t.RIGHT, "Second");
		type2str.put(Item.Screw.screw_t.UNKNOWN, "None");
		
		init();
		
		this.user=user;
		run();
	}
	
	
	public Item id_new_f(){
		return id_new;
	}
	
	/*
	 * main funciton with state machine that handles four step process to add
	 * new order or control
	 * First an barcode of order drawing no. is scanned, than it's drawing no., 
	 * in next step user select if it's new order or new control. Fourth step is 
	 * specifying threads or type of control and last is number of pieces
	*/
	private void run(){
		String number="0";
		String batch="0";
		int numberOf=0;
		Object[] choice={"","",Item.Screw.screw_t.UNKNOWN};
		int step=0;
		int maxStep=4;
		choose_e choise_b = choose_e.NOTHING;
		Control.COUNT count = Control.COUNT.UNKNOWN;
		do{
			BackSpace=false;
			
			if(step==0){
				number = getNumber();
				
				if(BackSpace||Exit){
					close();
					return;
				}
				else {step++;Enter=false;}
			}
			
			if(step==1){
				batch = getBatch();
			
				if(BackSpace) {step--; BackSpace=false;}
				else if(Exit) {close(); return;}
				else {step++; Enter=false;}
			}
			
			if(step==2){
				choise_b=isControl();
				
				if(BackSpace) {step--; BackSpace=false;}
				else if(Exit) {close(); return;}
				else if(choise_b.equals(choose_e.ROLLING)){maxStep=4; step++; Enter=false;}
				else { maxStep=3; step++; Enter=false;}
			}
			
			if(step==3){
				if(choise_b.equals(choose_e.ROLLING)) choice=thread(Integer.parseInt(number));
				else count=howMany();
			
				if(BackSpace) {step--; BackSpace=false;}
				else if(Exit) {close(); return;}
				else if(choise_b.equals(choose_e.ROLLING)){step++; Enter=false;}
			}
			
			if(step==4){ 
				numberOf=NumberOf();
			
				if(BackSpace) {step--; BackSpace=false;}
				else if(Exit) {close(); return;}
			}
			
		}while(step!=maxStep); //maybe add if there isn't any order with same drawing no. and batch no.
		
		Date now = Date.from(LocalDateTime.now()
			      .atZone(ZoneId.systemDefault())
			      .toInstant());
		
		if(choise_b.equals(choose_e.ROLLING)){
			Item item = new Item(now,
					new State(State.inProgress),
					java.util.UUID.randomUUID().toString(),
					user,
					batch,
					number);
		
			item.setNumberOf(numberOf);
			item.setScrew(java.util.UUID.randomUUID().toString(),(String)choice[0],(String)choice[1],(Item.Screw.screw_t)choice[2]); 
			if(DialogBoxes.ConfBox("Do you want to create a new order with following specificaitons ?\n\r "
					+ "Drawing no. : "+number
					+"\n\r Batch no.: "+batch +"\n\r","Creation of new order").get().getButtonData() == ButtonData.OK_DONE){
				try {
					db.saveItem(item);
					db.saveRecord(item);
					id_new=item;
					
					db.saveUser(item.getUser().setLast(item.getID()));
				} catch (SQLException e) {
					DialogBoxes.ErrorBox("Error occurred while connecting to database");
					Log.StackTrace(e);
				}
			}	
		}
		else if(choise_b.equals(choose_e.CONTROL)){
			System.out.println(count);
			Control control = new Control(java.util.UUID.randomUUID().toString(),
											batch,
											number,
											user,
											count,
											now);
			control.setState(new State(State.inProgress));
			try{
				if(db.exist(control,new State(State.inProgress))){
					DialogBoxes.ErrorBox("There is already same type control in progress");
				}
				else if(DialogBoxes.ConfBox("Do you want to create new control with following specifications ?\n\r "
						+ "Drawing no. : "+number
						+"\n\r Control no. : "+Control.count2str(count)+"\n\r","Creation of new control").get().getButtonData() == ButtonData.OK_DONE){
					db.saveControl(control);
					db.saveControl_h(control);
					id_new=control;
					
					db.saveUser(control.getUser().setLast(control.getID()));
				}
			}catch (SQLException e) {
				DialogBoxes.ErrorBox("Error occurred while connecting to database");
				Log.StackTrace(e);
			}
		}
		
		frame.requestFocus(); //because dialog has no parent it causes problems with focus
		close();
	}

	//loads batch number
	private String getBatch(){
		setUpFirst();
		update();
		frame.requestFocus(); //focus so key event properly works
		frame.setAlwaysOnTop(true);
	
		instruction.setText("Scan the barcode");
		code.setText("0");
		
		String batch = reader.loadBatch();
		
		while(batch==null&&!BackSpace&&!Exit){
			batch=reader.loadBatch();
		}
		
		code.setText(batch);
		
		frame.setAlwaysOnTop(false);
		
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			Log.StackTrace(e);
			Log.ErrorLog("Interrupt error see StactTrace log");
		}
		
		return batch;
	}
	
	//loads drawing number
	private String getNumber(){
		setUpFirst();
		update();
		frame.requestFocus();
		frame.setAlwaysOnTop(true);
		
		instruction.setText("Scan the barcode of the drawing no.");
		code.setText("0");
		
		String number = reader.loadNumber();
		
		while(number==null&&!BackSpace&&!Exit){
			number=reader.loadNumber();
		}
		
		code.setText(number);
		
		frame.setAlwaysOnTop(false);
		
		try {
			Thread.sleep(1100);
		} catch (InterruptedException e) {
			Log.StackTrace(e);
			Log.ErrorLog("Interrupt error see StactTrace log");
		}
		
		return number;
	}
	
	//function to add new component to grid layout
	void addManager(int x, int y, int fill, Component o, GridBagConstraints c, JPanel panel, Insets i,int font_v, KeyListener l){
		c.fill=fill;
		c.gridx=x;
		c.gridy=y;
		c.insets=i;
		
		o.setFont(new Font(o.getFont().getName(),Font.PLAIN,font_v));
		o.addKeyListener(l);
		
		panel.add(o,c);
	} 

	//by default used function with minimum parameters
	private void addManager(int x, int y, int fill, Component o, GridBagConstraints c, JPanel panel, Insets i){ 
		addManager(x, y, fill, o, c, panel, i,20,KeyListen_o);
	}

	//used for combo boxes, to use custom key listener
	private void addManager(int x, int y, int fill, Component o, GridBagConstraints c, JPanel panel, Insets i,KeyListener l){
		addManager(x, y, fill, o, c, panel, i,20,l);
	}
	
	//selecting if user is adding new control or new order
	private choose_e isControl(){
		control_pressed=false;
		rolling_pressed=false;
		
		JPanel panel2 = new JPanel();
		
		GridBagLayout grid = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		panel2.setLayout(grid);
		
		JButton control = new JButton("Controll");
		JButton rolling = new JButton("Rolling");
		
		control.addActionListener(l->control_pressed=true);
		rolling.addActionListener(l->rolling_pressed=true);
		
		int hgap = frame.getWidth()/8;
		
		class KeyListen_l extends KeyListen{
			int position = 0;
			
			@Override
			public void keyPressed(KeyEvent e){
				switch(e.getKeyCode()){
					case KeyEvent.VK_LEFT:
						control.requestFocus();
						position=0;
						break;
					case KeyEvent.VK_RIGHT:
						rolling.requestFocus();
						position=1;
						break;
					case KeyEvent.VK_ENTER:
						if(position==0) control.doClick();
						else rolling.doClick();
				}
			}
		}
		
		KeyListen_l listener = new KeyListen_l();
		
		addManager(0,0,GridBagConstraints.HORIZONTAL,control,c,panel2,new Insets(0,hgap,0,hgap),listener);
		addManager(1,0,GridBagConstraints.HORIZONTAL,rolling,c,panel2,new Insets(0,hgap,0,hgap),listener);
		
		frame.setContentPane(panel2);
		frame.addKeyListener(listener);
		control.requestFocus();
		update();
		
		while(!BackSpace&&!Exit&&!control_pressed&&!rolling_pressed){
			String text = reader.loadText();
			if(text!=null&&text=="control") control_pressed=true;
			else if(text!=null&&text=="rolling") rolling_pressed=true;
			
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				Log.StackTrace(e);
				Log.ErrorLog("Interrupt error see StactTrace log");
			}
		}
		
		if(!BackSpace&&!Exit){
			if(control_pressed) return choose_e.CONTROL;
			else return choose_e.ROLLING;
		}
		else return choose_e.NOTHING;
	}

	//chooses control type TODO: change name of function
	private Control.COUNT howMany(){
		JPanel panel3 = new JPanel();
		
		GridBagLayout grid = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		panel3.setLayout(grid);
		
		String[] listA = {"First","Second"};
		
		JLabel instruction = new JLabel("Choose control type");
		JComboBox<String> input = new JComboBox<String>(listA);
		
		int hgap = frame.getWidth()/2;
		int vgap = frame.getHeight()/16;
		
		class KeyListener_l extends KeyListen{
			int enter_num=0;
			
			@Override
			public void keyPressed(KeyEvent e){
				if(e.getKeyCode()==KeyEvent.VK_ENTER){
					SwingUtilities.invokeLater(()->input.showPopup());
					enter_num++;
					if(enter_num==2){
						input.hidePopup();
						frame.requestFocus();
						Enter=true;
					}
				}
			}
		}
		KeyListener_l listener = new KeyListener_l();
		
		addManager(0,0,GridBagConstraints.HORIZONTAL,instruction,c,panel3,new Insets(vgap,hgap,vgap,hgap),30,listener);
		addManager(0,1,GridBagConstraints.HORIZONTAL,input,c,panel3,new Insets(vgap,hgap,vgap,hgap),20,listener);
		
		frame.getContentPane().removeAll();
		frame.setContentPane(panel3);
		input.requestFocus();
		update();
		
		while(!BackSpace&&!Exit){
			while(!Enter&&!BackSpace&&!Exit){
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					Log.StackTrace(e);
					Log.ErrorLog("Interrupt error see StactTrace log");
				}
			}
			
			if(!BackSpace&&!Exit){
				Enter=false;
				return Control.str2count((String)input.getSelectedItem());
			}
		}
		return Control.COUNT.UNKNOWN;
	}
	
	//select thread type
	private Object[] thread(int number){
		JPanel panel2 = new JPanel();
		
		GridBagLayout grid = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		panel2.setLayout(grid);
		
		JLabel left_l = new JLabel("Thread type of first side:");
		JLabel right_l = new JLabel("Thread type of second side:");
		JLabel choise_l = new JLabel("Rolling side:");
		
		{left_l.setHorizontalAlignment(JLabel.CENTER);right_l.setHorizontalAlignment(JLabel.CENTER);choise_l.setHorizontalAlignment(JLabel.CENTER);}
		
		Setting conf = new Setting();
		
		String[] listC = conf.getListOfThreads();
		String[] listCh = {type2str.get(Item.Screw.screw_t.LEFT),type2str.get(Item.Screw.screw_t.RIGHT),type2str.get(Item.Screw.screw_t.UNKNOWN)};
		ArrayList<String> listC_A = new ArrayList<>(Arrays.asList(listC));
		
		String left_t="";
		String right_t="";
		
		try{// not ideal method of getting Screw object
			left_t = db.thread_by_number(number,Item.Screw.screw_t.LEFT); 
			right_t = db.thread_by_number(number,Item.Screw.screw_t.RIGHT);
		}catch(SQLException e){
			Log.StackTrace(e);
			Log.WarningLog("Error occurred while connecting to database see StackTrace");
		}
		
		JComboBox<String> left = new JComboBox<>(listC);
		JComboBox<String> right = new JComboBox<>(listC);
		JComboBox<String> choise = new JComboBox<>(listCh);
		
		((JLabel)left.getRenderer()).setHorizontalAlignment(JLabel.CENTER);
		((JLabel)right.getRenderer()).setHorizontalAlignment(JLabel.CENTER);
		((JLabel)choise.getRenderer()).setHorizontalAlignment(JLabel.CENTER);
		
		{left.setBackground(Color.WHITE);right.setBackground(Color.WHITE);choise.setBackground(Color.WHITE);}
		
		if(listC_A.indexOf(left_t)!=-1) left.setSelectedIndex(listC_A.indexOf(left_t));
		if(listC_A.indexOf(right_t)!=-1) right.setSelectedIndex(listC_A.indexOf(right_t));
		
		int vgap = frame.getHeight()/12;
		int hgap = frame.getWidth()/6;
		
		@SuppressWarnings("rawtypes")
		class KeyListen_l extends KeyListen{
			private int position=0;
			
			private JComboBox[] comboA = {left,right,choise};
			
			private boolean popupE = false;
			
			@Override
			public void keyPressed(KeyEvent e) {
				switch(e.getKeyCode()){
				case KeyEvent.VK_DOWN:
					if(!popupE){
						//to prevent opening item list by pressing key down
						if(position!=2) position++; 
						comboA[position].requestFocus();
						
						SwingUtilities.invokeLater(()->comboA[position].hidePopup());
					}
					break;
				case KeyEvent.VK_UP:
					if(position!=0&&!popupE){
						position--;
						comboA[position].requestFocus();
					}
					break;
				case KeyEvent.VK_ENTER:
					if(!popupE){
						SwingUtilities.invokeLater(()->{
					    	{
								comboA[position].showPopup();
					       		popupE=true;
					    	}
						});
					}
					else{
						popupE=false;
						if(position==2) Enter=true;
					}
					
					break;
				}
			}
		}
		
		KeyListen_l listener = new KeyListen_l();
		
		addManager(0,0,GridBagConstraints.HORIZONTAL,left_l,c,panel2,new Insets(vgap,hgap,vgap,hgap));
		addManager(1,0,GridBagConstraints.HORIZONTAL,left,c,panel2,new Insets(vgap,0,vgap,hgap),listener);
		addManager(0,1,GridBagConstraints.HORIZONTAL,right_l,c,panel2,new Insets(vgap,hgap,vgap,hgap));
		addManager(1,1,GridBagConstraints.HORIZONTAL,right,c,panel2,new Insets(vgap,0,vgap,hgap),listener);
		addManager(0,2,GridBagConstraints.HORIZONTAL,choise_l,c,panel2,new Insets(vgap,hgap,vgap,hgap));
		addManager(1,2,GridBagConstraints.HORIZONTAL,choise,c,panel2,new Insets(vgap,0,vgap,hgap),listener);
		
		frame.setContentPane(panel2);
		frame.addKeyListener(listener);
		left.requestFocus();
		update();
		
		while(!Enter&&!BackSpace&&!Exit){
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				Log.StackTrace(e);
				Log.ErrorLog("interrupt error see StactTrace log");
			}
		}
		
		if(!BackSpace&&!Exit){
			String left_box = (String)left.getSelectedItem();
			String right_box = (String)right.getSelectedItem();
			Item.Screw.screw_t rs = ((String)choise.getSelectedItem()).equals(type2str.get(Item.Screw.screw_t.LEFT)) ? Item.Screw.screw_t.LEFT : Item.Screw.screw_t.RIGHT;
			
			if(((String)choise.getSelectedItem()).equals(type2str.get(Item.Screw.screw_t.UNKNOWN))) rs = Item.Screw.screw_t.UNKNOWN;
			
			Object[] to_return = {left_box,right_box,rs};
			
			return to_return;
		}
		else return null;
	}
	
	//user types number of pieces 
	public int NumberOf(){
		JPanel panel3 = new JPanel();
		
		GridBagLayout grid = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		panel3.setLayout(grid);
		
		JLabel instruction = new JLabel("Type number of pieces");
		JTextField input = new JTextField();
		
		int hgap = frame.getWidth()/2;
		int vgap = frame.getHeight()/16;
		
		addManager(0,0,GridBagConstraints.HORIZONTAL,instruction,c,panel3,new Insets(vgap,hgap,vgap,hgap),30,KeyListen_o);
		addManager(0,1,GridBagConstraints.HORIZONTAL,input,c,panel3,new Insets(vgap,hgap,vgap,hgap),20,KeyListen_o);
		
		frame.getContentPane().removeAll();
		frame.setContentPane(panel3);
		input.requestFocus();
		update();
		
		while(!BackSpace&&!Exit){
			while(!Enter&&!BackSpace&&!Exit){
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					Log.StackTrace(e);
					Log.ErrorLog("Interrupt error see StactTrace log");
				}
			}
			
			if(!BackSpace&&!Exit){
				try{
					Enter=false;
					int output = Integer.parseInt(input.getText());
					return output;
				}catch(NumberFormatException e){
					DialogBoxes.InfoBox("Only numbers are allowed");
					input.requestFocus();
				}
			}
		}
		
		return 0;
	}
	
	@Override
	protected void finalize(){
		frame.setVisible(false);
	}

	
}
