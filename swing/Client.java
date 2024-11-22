//
// Client Java to communicate with the C++ server
// eric lecolinet - telecom paristech - 2015
//

import java.io.*;
import java.net.*;

/**
 * <p>
 * Client class to communicate with a server using sockets.
 * </p>
 *
 * <p>
 * This client connects to a server using TCP sockets, sends requests entered by the user,
 * and displays the server's responses.
 * </p>
 * 
 * @author Eric Lecolinet - Telecom ParisTech - 2015
 */
public class Client {
    private static final long serialVersionUID = 1L;

    /** Default server address. */
    static final String DEFAULT_HOST = "localhost";

    /** Default server port. */
    static final int DEFAULT_PORT = 3331;

    /** Socket to connect to the server. */
    private Socket sock;

    /** Input stream to read responses from the server. */
    private BufferedReader input;

    /** Output stream to send requests to the server. */
    private BufferedWriter output;

    /**
     * Main program to interact with the server via the console.
     *
     * @param argv Command-line arguments (optional host and port).
     */
    public static void main(String argv[]) {
        String host = DEFAULT_HOST;
        int port = DEFAULT_PORT;
        if (argv.length >= 1)
            host = argv[0];
        if (argv.length >= 2)
            port = Integer.parseInt(argv[1]);

        Client client = null;

        try {
            client = new Client(host, port);
        } catch (Exception e) {
            System.err.println("Client: Couldn't connect to " + host + ":" + port);
            System.exit(1);
        }

        System.out.println("Client connected to " + host + ":" + port);

        // Read user input from the console
        BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            System.out.print("Request: ");
            try {
                String request = cin.readLine();
                String response = client.send(request);
                System.out.println("Response: " + response);
            } catch (java.io.IOException e) {
                System.err.println("Client: IO error");
                return;
            }
        }
    }

    /**
     * Initializes the connection to the server.
     *
     * @param host The server address.
     * @param port The server port.
     * @throws UnknownHostException If the server cannot be found.
     * @throws IOException          If an I/O error occurs.
     */
    public Client(String host, int port) throws UnknownHostException, IOException {
        try {
            sock = new java.net.Socket(host, port);
        } catch (java.net.UnknownHostException e) {
            System.err.println("Client: Couldn't find host " + host + ":" + port);
            throw e;
        } catch (java.io.IOException e) {
            System.err.println("Client: Couldn't reach host " + host + ":" + port);
            throw e;
        }

        try {
            input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
        } catch (java.io.IOException e) {
            System.err.println("Client: Couldn't open input or output streams");
            throw e;
        }
    }

    /**
     * Sends a request to the server and returns its full response.
     *
     * @param request The request to send.
     * @return The server's response, or an error message if an exception occurs.
     */
    public String send(String request) {
        try {
            // Send the request to the server
            output.write(request + "\n");
            output.flush();

            // Read the server's full response
            StringBuilder responseBuilder = new StringBuilder();
            String line;
            while ((line = input.readLine()) != null) {
                // Stop reading when <END> is encountered
                if (line.endsWith("<END>")) {
                    responseBuilder.append(line.replace("<END>", "")).append("\n");
                    break;
                }
                responseBuilder.append(line).append("\n");
            }

            // Return the complete response
            return responseBuilder.toString().trim();
        } catch (IOException e) {
            return "Error: " + e.getMessage();
        }
    }
}
