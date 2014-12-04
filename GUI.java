import java.io.*;
import java.net.*;
import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.event.*;

public class GUI extends JFrame
{
    private static final long serialVersionUID = 1L;

    JTextArea text = new JTextArea("");
    JScrollPane textscroll = new JScrollPane(text);
    JPanel buttons = new JPanel();
    JButton searchbutton = new JButton("Search");
    JButton playbutton = new JButton("Play");
    JButton readbutton = new JButton("Read");
    JButton writebutton = new JButton("Write");
    JMenuBar menubar = new JMenuBar();
    JMenu menu = new JMenu("menu");
    JMenuItem searchitem = new JMenuItem("Search");
    JMenuItem playitem = new JMenuItem("Play");
    JMenuItem readitem = new JMenuItem("Read");
    JMenuItem writeitem = new JMenuItem("Write");
    JMenuItem closeitem = new JMenuItem("Quit");
    JToolBar toolbar = new JToolBar("toolbar");

    Client client;
    String host = Client.DEFAULT_HOST;
    int port = Client.DEFAULT_PORT;

    public static void main(String args[])
    {
	new GUI("MultFS");
    }

    public GUI(String name)
    {
	super(name);
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	try{
	    client = new Client(host, port);
	}
	catch (Exception e) {
	    System.out.println("Client: couldn't connect: "+host+":"+port);
	    System.exit(1);
	}
	
	add(textscroll);
	buttons.add(searchbutton, BorderLayout.NORTH);
	buttons.add(readbutton, BorderLayout.WEST);
	buttons.add(writebutton, BorderLayout.EAST);	
	buttons.add(playbutton, BorderLayout.SOUTH);	
	add(buttons, BorderLayout.SOUTH);

	searchbutton.addActionListener(new SearchAction());
	playbutton.addActionListener(new PlayAction());
	readbutton.addActionListener(new ReadAction());
	writebutton.addActionListener(new WriteAction());

	searchitem.addActionListener(new SearchAction());
	playitem.addActionListener(new PlayAction());
	readitem.addActionListener(new ReadAction());
	writeitem.addActionListener(new WriteAction());
	closeitem.addActionListener(new CloseAction());

	menu.add(searchitem);
	menu.add(playitem);
	menu.add(readitem);
	menu.add(writeitem);
	menu.add(closeitem);

	//toolbar.add(new AddTextAction1());
	//toolbar.add(new AddTextAction2());
	//toolbar.add(new CloseListener());

	menubar.add(menu);
	//menubar.add(toolbar);

	setJMenuBar(menubar);

	pack();
	setVisible(true);
    }

    //! Action which sends a search request to the server
    private class SearchAction extends AbstractAction { 
	public void actionPerformed(ActionEvent e) { 
	    String name = JOptionPane.showInputDialog("Please enter a name to search");
	    String response = client.send("search "+name);
	    text.append(response+'\n');
	} 
    } 

    //! Action which sends a play request to the server
    private class PlayAction extends AbstractAction { 
	public void actionPerformed(ActionEvent e) { 
	    String name = JOptionPane.showInputDialog("Please enter a name to play");
	    String response = client.send("play "+name); 
	    text.append(response+'\n');
	}
    }

    //! Action which reads from text file
    private class ReadAction extends AbstractAction { 
	public void actionPerformed(ActionEvent e) {
	    String name;
	    if(host == "localhost")
		{
		    final JFileChooser fc = new JFileChooser();
		    int returnVal = fc.showOpenDialog(GUI.this);
		    if (returnVal == JFileChooser.APPROVE_OPTION) {
			File file = fc.getSelectedFile();
			name = file.getPath();// + file.getName();
		    } else {
			return;
		    }
		}
	    else
		{
		    name = JOptionPane.showInputDialog("Please enter file to read from");
		}
	    String response = client.send("read "+name); 
	    text.append(response+'\n');
	} 
    } 

    //! Action which reads from text file
    private class WriteAction extends AbstractAction { 
	public void actionPerformed(ActionEvent e) { 
	    String name = JOptionPane.showInputDialog("Please enter file to write to");
	    String response = client.send("write "+name); 
	    text.append(response+'\n');
	} 
    } 

    //! Action to be performed when button 3 is pressed
    private class CloseAction extends AbstractAction { 
	public void actionPerformed(ActionEvent e) { 
	    System.exit(0);
	} 
    } 

}
