/**
 * MainWindow class for the Media Center client.
 *
 * <p>
 * This class creates the GUI for the Media Center client application.
 * It provides a window with menu and toolbar options to interact with the server,
 * such as playing media, listing media, listing groups, and displaying help information.
 * </p>
 *
 * @author
 */
import java.awt.*;
import java.io.*;
import java.net.*;
import javax.swing.*;

public class MainWindow extends JFrame {

    private static final long serialVersionUID = 1L;

    /** Default server details */
    static String DEFAULT_HOST = "localhost";
    static int DEFAULT_PORT = 3331;
    static String host = DEFAULT_HOST;
    static int port = DEFAULT_PORT;

    /** Client connection */
    static Client client = null;

    /** UI components */
    static JTextArea textZone;

    /**
     * Constructor to initialize the GUI.
     */
    public MainWindow() {
        super("Media Center");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Create the text zone
        textZone = new JTextArea(15, 30);
        textZone.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textZone);
        add(scrollPane, BorderLayout.CENTER);

        // Create the menu and toolbar
        createMenuBar();
        createToolBar();

        // Display the window
        pack();
        setVisible(true);
    }

    /**
     * Creates the menu bar with various actions.
     */
    private void createMenuBar() {
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Menu");

        JMenuItem playMediaItem = new JMenuItem("Play Media");
        playMediaItem.addActionListener(e -> handlePlayMedia());
        menu.add(playMediaItem);

        JMenuItem listMediaItem = new JMenuItem("List Media");
        listMediaItem.addActionListener(e -> handleListMedia());
        menu.add(listMediaItem);

        JMenuItem listGroupsItem = new JMenuItem("List Groups");
        listGroupsItem.addActionListener(e -> handleListGroups());
        menu.add(listGroupsItem);

        JMenuItem helpItem = new JMenuItem("Help");
        helpItem.addActionListener(e -> handleHelp());
        menu.add(helpItem);

        // New Clear Text menu item
        JMenuItem clearTextItem = new JMenuItem("Clear Text");
        clearTextItem.addActionListener(e -> handleClearText());
        menu.add(clearTextItem);

        JMenuItem exitItem = new JMenuItem("Exit");
        exitItem.addActionListener(e -> System.exit(0));
        menu.add(exitItem);

        menuBar.add(menu);
        setJMenuBar(menuBar);
    }

    /**
     * Creates the toolbar with various actions.
     */
    private void createToolBar() {
        JToolBar toolBar = new JToolBar();

        JButton playMediaButton = new JButton("Play Media");
        playMediaButton.addActionListener(e -> handlePlayMedia());
        toolBar.add(playMediaButton);

        JButton listMediaButton = new JButton("List Media");
        listMediaButton.addActionListener(e -> handleListMedia());
        toolBar.add(listMediaButton);

        JButton listGroupsButton = new JButton("List Groups");
        listGroupsButton.addActionListener(e -> handleListGroups());
        toolBar.add(listGroupsButton);

        JButton helpButton = new JButton("Help");
        helpButton.addActionListener(e -> handleHelp());
        toolBar.add(helpButton);

        // New Clear Text button
        JButton clearTextButton = new JButton("Clear Text");
        clearTextButton.addActionListener(e -> handleClearText());
        toolBar.add(clearTextButton);

        JButton exitButton = new JButton("Exit");
        exitButton.addActionListener(e -> System.exit(0));
        toolBar.add(exitButton);

        add(toolBar, BorderLayout.NORTH);
    }

    // Action handlers

    /**
     * Handles the "Play Media" action.
     * Prompts the user for the media name and sends a play request to the server.
     */
    private void handlePlayMedia() {
        String mediaName = JOptionPane.showInputDialog(this, "Enter the name of the media to play:");
        if (mediaName == null || mediaName.trim().isEmpty()) {
            textZone.append("No media name entered.\n");
            return;
        }
        String request = "play " + mediaName.trim();
        String response = client.send(request);
        textZone.append("Server Response:\n" + response + "\n");
    }

    /**
     * Handles the "List Media" action.
     * Sends a request to list all media and displays the response.
     */
    private void handleListMedia() {
        String response = client.send("listMedia");
        textZone.append("Server Response:\n" + response + "\n");
    }

    /**
     * Handles the "List Groups" action.
     * Sends a request to list all groups and displays the response.
     */
    private void handleListGroups() {
        String response = client.send("listGroups");
        textZone.append("Server Response:\n" + response + "\n");
    }

    /**
     * Handles the "Help" action.
     * Sends a help request to the server and displays the response.
     */
    private void handleHelp() {
        String response = client.send("help");
        textZone.append("Server Response:\n" + response + "\n");
    }

    /**
     * Handles the "Clear Text" action.
     * Clears the text area.
     */
    private void handleClearText() {
        textZone.setText("");
    }

    // Client class for server communication

    /**
     * Inner Client class to handle server communication.
     */
    private static class Client {
        private Socket socket;
        private BufferedReader input;
        private BufferedWriter output;

        /**
         * Constructs a Client object and establishes a connection to the server.
         *
         * @param host The server's hostname.
         * @param port The server's port number.
         * @throws IOException If an I/O error occurs when creating the socket.
         */
        public Client(String host, int port) throws IOException {
            socket = new Socket(host, port);
            input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        }

        /**
         * Sends a request to the server and returns the response.
         *
         * @param request The request string to send.
         * @return The server's response.
         */
        public String send(String request) {
            try {
                output.write(request + "\n");
                output.flush();

                // Read multi-line response from server
                StringBuilder response = new StringBuilder();
                String line;
                while ((line = input.readLine()) != null) {
                    if (line.endsWith("<END>")) {
                        response.append(line.replace("<END>", "")).append("\n");
                        break;
                    }
                    response.append(line).append("\n");
                }
                return response.toString().trim();
            } catch (IOException e) {
                return "Error: " + e.getMessage();
            }
        }
    }

    /**
     * Main method to start the application.
     *
     * @param args Command-line arguments for host and port.
     */
    public static void main(String[] args) {
        if (args.length > 0)
            host = args[0];
        if (args.length > 1)
            port = Integer.parseInt(args[1]);

        try {
            client = new Client(host, port);
            SwingUtilities.invokeLater(MainWindow::new);
        } catch (IOException e) {
            System.err.println("Failed to connect to the server: " + e.getMessage());
        }
    }
}
