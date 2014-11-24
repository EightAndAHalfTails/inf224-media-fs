import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
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

	pack();
	setVisible(true);
    }

    class AddTextAction1 implements ActionListener { 
	public void actionPerformed(ActionEvent e) { 
	    text.append("You pressed button1\n"); 
	} 
    } 

    class AddTextAction2 implements ActionListener { 
	public void actionPerformed(ActionEvent e) { 
	    text.append("You pressed button2\n"); 
	} 
    } 

    class CloseListener implements ActionListener { 
	public void actionPerformed(ActionEvent e) { 
	    System.exit(0); 
	} 
    } 

}