import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.event.*; 

public class GUI extends JFrame
{
    private static final long serialVersionUID = 1L;

    JTextArea text = new JTextArea("Enter text...");
    JScrollPane textscroll = new JScrollPane(text);
    JPanel buttons = new JPanel();
    JButton button1 = new JButton("Button 1");
    JButton button2 = new JButton("Button 2");
    JButton button3 = new JButton("Button 3");
    JMenuBar menubar = new JMenuBar();
    JMenu menu = new JMenu("menu");
    JMenuItem menuitem1 = new JMenuItem("Action 1");
    JMenuItem menuitem2 = new JMenuItem("Action 2");
    JMenuItem menuitem3 = new JMenuItem("Action 3");
    JToolBar toolbar = new JToolBar("toolbar");

    public static void main(String args[])
    {
	new GUI("MultFS");
    }

    public GUI(String name)
    {
	super(name);
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	add(textscroll);
	buttons.add(button1, BorderLayout.WEST);
	buttons.add(button2);
	buttons.add(button3, BorderLayout.EAST);	
	add(buttons, BorderLayout.SOUTH);

	button1.addActionListener(new AddTextAction1());
	button2.addActionListener(new AddTextAction2());
	button3.addActionListener(new CloseListener());

	menuitem1.addActionListener(new AddTextAction1());
	menuitem2.addActionListener(new AddTextAction2());
	menuitem3.addActionListener(new CloseListener());

	menu.add(menuitem1);
	menu.add(menuitem2);
	menu.add(menuitem3);

	toolbar.add(new AddTextAction1());
	toolbar.add(new AddTextAction2());
	toolbar.add(new CloseListener());

	menubar.add(menu);
	menubar.add(toolbar);

	setJMenuBar(menubar);

	pack();
	setVisible(true);
    }

    //! Action to be performed when button 1 is pressed
    private class AddTextAction1 extends AbstractAction { 
	public void actionPerformed(ActionEvent e) { 
	    text.append("You pressed button1\n"); 
	} 
    } 

    //! Action to be performed when button 2 is pressed
    private class AddTextAction2 extends AbstractAction { 
	public void actionPerformed(ActionEvent e) { 
	    text.append("You pressed button2\n"); 
	} 
    } 

    //! Action to be performed when button 3 is pressed
    private class CloseListener extends AbstractAction { 
	public void actionPerformed(ActionEvent e) { 
	    System.exit(0);
	} 
    } 

}