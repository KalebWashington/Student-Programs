package gpajava;
import java.io.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Pattern;
public class GPAJava {

    
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        String last;
        ArrayList <String[]> grades = new ArrayList<>();
        int i=0;
        Scanner input = new Scanner(System.in);        
        System.out.println("Enter the Last Name.");
        Pattern namevalid = Pattern.compile("[aA-zZ]*");
        while(!input.hasNext(namevalid)){
            System.out.println("Invalid Last Name.");
            System.out.println("Enter Last Name.");
            input.next();
        }
        last = input.next();
        String user = "SELECT Grade,Section_ID from Grade_tbl where Student_ID=(Select Student_ID from Student_tbl where Last_name=?);";
        System.out.println("Attempting connection.");
        String driver = "com.mysql.jdbc.Driver";
        String url = "jdbc:mysql://localhost:3306/Student_Example?autoReconnect=true&useSSL=false";
        Class.forName(driver);
        Connection conn = DriverManager.getConnection(url,"root","CSI-04");
        PreparedStatement statement = conn.prepareStatement(user);
        statement.setString(1,last);
        ResultSet grade=statement.executeQuery();
        int columnCount=grade.getMetaData().getColumnCount();
        while(grade.next())
        {
            String[] row=new String[columnCount];
            for(i=0;i<columnCount;i++)
            {
                row[i]=grade.getString(i+1);
            }
            grades.add(row);
        }
        System.out.println(grades);
        conn.close();

    }
    
}
