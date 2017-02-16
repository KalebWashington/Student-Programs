package javadatabaseprogram;

import java.util.Scanner;
import java.sql.*;
import java.util.regex.Pattern;


public class JavaDatabaseProgram{
    
    public static void main(String args[])throws ClassNotFoundException, SQLException{
        
        String first, last, ssn, number;
        Scanner input = new Scanner(System.in);
        System.out.println("Enter the First Name.");
        Pattern namevalid = Pattern.compile("[aA-zZ]*");
        while(!input.hasNext(namevalid)){
            System.out.println("Invalid First Name.");
            System.out.println("Enter First Name.");
            input.next();
        }
        first = input.next();
            
        System.out.println("Enter the Last Name.");
        while(!input.hasNext(namevalid)){
            System.out.println("Invalid Last Name.");
            System.out.println("Enter Last Name.");
            input.next();
        }
        last = input.next();
        
                Pattern phonevalid = Pattern.compile("[0-9]{10}");
        System.out.println("Enter a single valid Phone Number.");
        while(!input.hasNextLong() || !input.hasNext(phonevalid)){
            System.out.println("invalid Phone Number.");
            System.out.println("Enter valid Phone Number.");
            input.next();
        }
        number = input.next();
            
        Pattern ssnvalid = Pattern.compile("[0-9]{9}");
        System.out.println("Enter the SSN of the Individual.");
        while(!input.hasNextLong() || !input.hasNext(ssnvalid)){
            System.out.println("invalid ssn.");
            System.out.println("Enter valid ssn.");
            input.next();
        }
        ssn = input.next();
        
        String user = "INSERT INTO People_tbl (First, Last, SSN, Phone_Number)" + "VALUES(?,?,?,?)";
        System.out.println("Attempting connection.");
        String driver = "com.mysql.jdbc.Driver";
        String url = "jdbc:mysql://localhost:3306/group4?autoReconnect=true&useSSL=false";
        Class.forName(driver);
        Connection conn = DriverManager.getConnection(url,"root","CSI-04");
        PreparedStatement statement = conn.prepareStatement(user);
        statement.setString(1, first);
        statement.setString(2, last);
        statement.setString(3, ssn);
        statement.setString(4, number);
        statement.executeUpdate();
        conn.close();
        System.out.println("Data Submitted");
    }
}
