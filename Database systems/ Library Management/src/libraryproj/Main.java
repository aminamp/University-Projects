/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package libraryproj;

import java.sql.*;
import javax.swing.table.*;
import javax.swing.JTable;
import java.util.Calendar;
import javax.swing.JOptionPane;


public class Main {
    
    
    
        static DefaultTableModel search(JTable restable, String searchby, String tex){
        Connection con = null;
        ResultSet rst = null;
        String rowinfo[] = new String[7];

         try {

            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Library", "root", "ENmPqspN");
            Statement stmt = con.createStatement();
            if(searchby.equals("Author's name"))
            {
            
                rst = stmt.executeQuery("select T1.book_id,T1.title,T1.author_name as authors,T1.branch_id,T1.no_of_copies,(T1.no_of_copies-ifnull(T2.book_loan,0)) as available_copies, T1.Type from(select book.book_id, book.title, group_concat(book_authors.author_name SEPARATOR ', ') as author_name, book_copies.branch_id, book_copies.no_of_copies, book_authors.Type from book,book_copies,book_authors where book.book_id=book_copies.book_id and book.book_id=book_authors.book_id and book.book_id IN (select book.book_id from book,book_authors where book_authors.author_name like '%"+tex+"%' and book.book_id=book_authors.book_id) group by book.book_id,book_copies.branch_id) as T1 left join (select count(*) as book_loan,book_id,branch_id from book_loans where date_in is null group by branch_id,book_id) as T2 on T1.branch_id = T2.branch_id and T1.book_id = T2.book_id order by T1.title,T1.branch_id;");

                
            }
            else if(searchby.equals("Book's title"))
            {
               
                
                rst = stmt.executeQuery("select T1.book_id,T1.title,T1.author_name as authors,T1.branch_id,T1.no_of_copies,(T1.no_of_copies-ifnull(T2.book_loan,0)) as available_copies, T1.Type from(select book.book_id, book.title, group_concat(book_authors.author_name SEPARATOR ', ') as author_name, book_copies.branch_id, book_copies.no_of_copies, book_authors.Type from book,book_copies,book_authors where book.book_id=book_copies.book_id and book.book_id=book_authors.book_id and book.title like '%"+tex+"%' group by book.book_id,book_copies.branch_id) as T1 left join (select count(*) as book_loan,book_id,branch_id from book_loans where date_in is null group by branch_id,book_id) as T2 on T1.branch_id = T2.branch_id and T1.book_id = T2.book_id order by T1.title,T1.branch_id;");       
            
                }
            else if(searchby.equals("Book's id"))
            {
                
                rst = stmt.executeQuery("select T1.book_id,T1.title,T1.author_name as authors,T1.branch_id,T1.no_of_copies,(T1.no_of_copies-ifnull(T2.book_loan,0)) as available_copies, T1.Type from(select book.book_id, book.title, group_concat(book_authors.author_name SEPARATOR ', ') as author_name, book_copies.branch_id, book_copies.no_of_copies, book_authors.Type from book,book_copies,book_authors where book.book_id=book_copies.book_id and book.book_id=book_authors.book_id and book.book_id like '%"+tex+"%' group by book.book_id,book_copies.branch_id) as T1 left join (select count(*) as book_loan,book_id,branch_id from book_loans where date_in is null group by branch_id,book_id) as T2 on T1.branch_id = T2.branch_id and T1.book_id = T2.book_id order by T1.title,T1.branch_id;");       
            
                }
            
            
            
            DefaultTableModel tablemodel = (DefaultTableModel)restable.getModel();
            tablemodel.setRowCount(0);
            
            while(rst.next())
            {
                rowinfo[0] = rst.getString("book_id");
                rowinfo[1] = rst.getString("title");
                rowinfo[2] = rst.getString("authors");
                rowinfo[3] = rst.getString("branch_id");
                rowinfo[4] = rst.getString("no_of_copies");
                rowinfo[5] = rst.getString("available_copies");
                rowinfo[6] = rst.getString("Type");
                tablemodel.addRow(rowinfo);
                
            }
            con.close();
            rst.close();
            if(restable.getRowCount()>0)
            restable.setRowSelectionInterval(0, 0);
            
            return tablemodel;
         }
         catch (SQLException e) {
            System.out.println("Error : " + e.getMessage());
            
            JOptionPane.showMessageDialog(null, "Invalid input!","ERROR",JOptionPane.ERROR_MESSAGE);
            return null;

        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
            return null;
        }
    }

    
    
    
    
    static void checkout(String book_id,String branch_id,String card_no){
        Connection con = null;
        ResultSet rst = null;
        ResultSet rst1 = null;
        ResultSet rst2 = null;
        try {

            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Library", "root", "ENmPqspN");
            Statement stmt = con.createStatement();
            int new_loan_id = 0;
            int borrowed = 0;
            int loan_copies = 0 ;
            int copies = 99;
            rst = stmt.executeQuery("select * from book_loans order by loan_id desc limit 1;");
            while(rst.next())
            {
            String loan_id = rst.getString("loan_id");
            new_loan_id = Integer.parseInt(loan_id)+1;
            }
            Calendar cal = Calendar.getInstance();
            java.text.SimpleDateFormat format = new java.text.SimpleDateFormat("yyyy-MM-dd");   
            String date_out = format.format(cal.getTime());
            cal.add(Calendar.DATE, 14);
            String due_date = format.format(cal.getTime());
            
            rst = stmt.executeQuery("select T1.no_of_bor from (select card_no,count(*) as no_of_bor from book_loans where date_in is null group by card_no) as T1 where card_no ="+ card_no+";");
            while(rst.next())
            {
               borrowed = Integer.parseInt(rst.getString("no_of_bor"));
            }
            rst = stmt.executeQuery("select count(*) as book_loan from book_loans where date_in is null and book_id = '"+book_id+"' and branch_id = "+branch_id+" group by branch_id,book_id;");
            while(rst.next())
            {
                loan_copies = Integer.parseInt(rst.getString("book_loan"));
       
            }   
            rst = stmt.executeQuery("select no_of_copies from book_copies where book_id = '"+book_id +"' and branch_id ="+branch_id+ ";");
            while(rst.next())
            {
                copies = Integer.parseInt(rst.getString("no_of_copies"));
            }
            
            int temp = 0;
            rst1 = stmt.executeQuery("select book_id from book_copies where book_id = '"+book_id +"' and branch_id ="+branch_id+ ";");
            if(!rst1.isBeforeFirst())
            {
              temp = 1;  
            }
            rst2 = stmt.executeQuery("select card_no from borrower where card_no ="+card_no+";");
            
            if( temp == 1 )
            {
                JOptionPane.showMessageDialog(null, "Invalid Book's id or Branch's id","ERROR",JOptionPane.ERROR_MESSAGE);
            }
            else if(!rst2.isBeforeFirst())
            {
                JOptionPane.showMessageDialog(null, "Invalid borrower's card_no","ERROR",JOptionPane.ERROR_MESSAGE);
            }
            else if(borrowed == 3)
            {
                JOptionPane.showMessageDialog(null, "Borrower can't borrow more than 3 books","ERROR",JOptionPane.ERROR_MESSAGE);
            }
            else if(copies == loan_copies)
            {
                JOptionPane.showMessageDialog(null, "No enough book copies","ERROR",JOptionPane.ERROR_MESSAGE);

            }
            else
            {
             stmt.executeUpdate("insert into book_loans values('"+new_loan_id+"','"+book_id+"','"+branch_id+"','"+card_no+"','"+date_out+"','"+due_date+"',null);"  );
            }
        }
        catch (SQLException e) {
            System.out.println("Error : " + e.getMessage());
            JOptionPane.showMessageDialog(null, "Invalid input!","ERROR",JOptionPane.ERROR_MESSAGE);
            

        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
            
        }
    }
    static DefaultTableModel checkindisplay(JTable checkintable,String searchby,String text){
        Connection con = null;
        ResultSet rst = null;
        String rowinfo[] = new String[7];

         try {

            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Library", "root", "ENmPqspN");
            Statement stmt = con.createStatement();
            if(searchby.equals("Book id"))
            {
                rst = stmt.executeQuery("select * from book_loans where date_in is null and book_id like '%"+text+"%';");       

            }
            else if(searchby.equals("Card number"))
            {
                Integer.parseInt(text);
                rst = stmt.executeQuery("select * from book_loans where date_in is null and card_no = "+text+";");       
            }
            else if(searchby.equals("Borrower name"))
            {
                rst = stmt.executeQuery("select loan_id,book_id,branch_id,card_no,date_out,due_date,date_in " +
"from(select loan_id,book_id,branch_id,book_loans.card_no,date_out,due_date,date_in,fname,lname from book_loans,borrower where book_loans.card_no = borrower.card_no and date_in is null) as T1 " +
"where T1.fname like '%"+text+"%' or T1.lname like '%"+text+"%' ;");       
            }
            DefaultTableModel tablemodel = (DefaultTableModel)checkintable.getModel();
            tablemodel.setRowCount(0);
            
            while(rst.next())
            {
                rowinfo[0] = rst.getString("loan_id");
                rowinfo[1] = rst.getString("book_id");
                rowinfo[2] = rst.getString("branch_id");
                rowinfo[3] = rst.getString("card_no");
                rowinfo[4] = rst.getString("date_out");
                rowinfo[5] = rst.getString("due_date");
                rowinfo[6] = rst.getString("date_in");
                tablemodel.addRow(rowinfo);
                
            }
            if(checkintable.getRowCount()>0)
            checkintable.setRowSelectionInterval(0, 0);
            
            return tablemodel;
         }
         catch (SQLException e) {
            System.out.println("Error : " + e.getMessage());
            
            JOptionPane.showMessageDialog(null, "Invalid input!","ERROR",JOptionPane.ERROR_MESSAGE);
            return null;

        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
            return null;
        }
    }
    
    static void checkin(int row,DefaultTableModel tablemodel,JTable checkintable){
        Connection con = null;
        ResultSet rst = null;
        try {

            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Library", "root", "ENmPqspN");
            Statement stmt = con.createStatement();
            String loan = tablemodel.getValueAt(row, 0).toString();
            int loan_id = Integer.parseInt(loan);
            Calendar cal = Calendar.getInstance();
            java.text.SimpleDateFormat format = new java.text.SimpleDateFormat("yyyy-MM-dd");   
            String date_in = format.format(cal.getTime());      //date_in will be set to local system time
            stmt.executeUpdate("update book_loans set date_in = '"+date_in+"' where loan_id ="+loan_id+";");
            JOptionPane.showMessageDialog(null, "Check in complete!","MESSAGE",JOptionPane.INFORMATION_MESSAGE);
        }
            
            catch (SQLException e) {
            System.out.println("Error : " + e.getMessage());
            
            JOptionPane.showMessageDialog(null, "Invalid input!","ERROR",JOptionPane.ERROR_MESSAGE);

        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
            
        tablemodel.removeRow(row);
        checkintable.setModel(tablemodel);
        if(checkintable.getRowCount()>0)
            checkintable.setRowSelectionInterval(0, 0);
    }
    static void createborrower(String fname,String lname,String address,String phone){
            Connection con = null;
            ResultSet rst = null;
            ResultSet rst1 = null;
            int new_card_no = 0;
           try {
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Library", "root", "ENmPqspN");
            Statement stmt = con.createStatement();
            rst = stmt.executeQuery("select * from borrower order by card_no desc limit 1;");
            while(rst.next())
            {
            String card_no = rst.getString("card_no");
            new_card_no = Integer.parseInt(card_no)+1;
            }
            rst1 = stmt.executeQuery("select * from borrower where fname = '"+fname+"' and lname = '"+lname+"' and address ='"+address+"';");
            if(rst1.next() == false)
            {
                stmt.executeUpdate("insert into borrower values('"+new_card_no+"','"+fname+"','"+lname+"','"+address+"','"+phone+"');");
                JOptionPane.showMessageDialog(null, "New borrower has been created!","MESSAGE",JOptionPane.INFORMATION_MESSAGE);
            }
            else 
                JOptionPane.showMessageDialog(null, "Borrower already exists!","ERROR",JOptionPane.ERROR_MESSAGE);

           }
           catch (SQLException e) {
            System.out.println("Error : " + e.getMessage());
            JOptionPane.showMessageDialog(null, "Invalid input!","ERROR",JOptionPane.ERROR_MESSAGE);
            

        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
            
        }
    }
    static DefaultTableModel refreshfine(JTable finetable){
        Connection con = null;
            ResultSet rst = null;
            String[] rowinfo = new String[4];
            try {
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Library", "root", "ENmPqspN");
            Statement stmt = con.createStatement();
            stmt.executeUpdate("INSERT IGNORE INTO fines(loan_id,fine_amt) SELECT T1.loan_id,T1.fine_amt FROM (select loan_id,datediff(curdate(),due_date)*0.25 as fine_amt from book_loans where date_in is null and curdate() > due_date UNION select loan_id,datediff(date_in,due_date)*0.25 as fine_amt from book_loans where date_in is not null and date_in > due_date) AS T1;");
            rst = stmt.executeQuery("select T1.card_no,fname,lname,fine_amt from (select card_no,sum(fine_amt) as fine_amt from fines,book_loans where paid = 0 and fines.loan_id = book_loans.loan_id group by card_no) AS T1,borrower where T1.card_no = borrower.card_no;");
            DefaultTableModel tm = (DefaultTableModel) finetable.getModel();
            tm.setRowCount(0);
             while(rst.next())
            {
                rowinfo[0] = rst.getString("card_no");
                rowinfo[1] = rst.getString("fname");
                rowinfo[2] = rst.getString("lname");
                rowinfo[3] = rst.getString("fine_amt");
                tm.addRow(rowinfo);
            }
            
            rst.close();
            
            return tm;
            
            }
           
             catch (SQLException e) {
            System.out.println("Error : " + e.getMessage());
            JOptionPane.showMessageDialog(null, "Invalid input!","ERROR",JOptionPane.ERROR_MESSAGE);
               return null;

        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
            return null;
            
        }
        
    }
    static DefaultTableModel showfines(int row,DefaultTableModel tm,JTable fineTable2){
         Connection con = null;
         ResultSet rst = null;
         String[] rowinfo = new String[3];

        try {

            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Library", "root", "ENmPqspN");
            Statement stmt = con.createStatement();
            String card_no_string = tm.getValueAt(row, 0).toString();
            
            int card_no = Integer.parseInt(card_no_string);
            rst = stmt.executeQuery("select book_loans.loan_id,fine_amt,paid from book_loans,fines where book_loans.card_no = "+ card_no +" and book_loans.loan_id = fines.loan_id;");
            DefaultTableModel ft = (DefaultTableModel) fineTable2.getModel();
            ft.setRowCount(0);
            while (rst.next())
            {
                rowinfo[0] = rst.getString("loan_id");
                rowinfo[1] = rst.getString("fine_amt");
                if(rst.getString("paid").equals("1"))
                    rowinfo[2] = "yes";
                else
                    rowinfo[2] = "no";
                ft.addRow(rowinfo);
                        
            }
            return ft;
        }
        catch (SQLException e) {
            System.out.println("Error : " + e.getMessage());
            JOptionPane.showMessageDialog(null, "Invalid input!","ERROR",JOptionPane.ERROR_MESSAGE);
            return null;

        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
            return null;
        }
        
    }
    static void makepay(int row,DefaultTableModel pm,JTable fineTable2){
         Connection con = null;
         ResultSet rst1 = null;
         String[] rowinfo = new String[3];
         
        try {

            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Library", "root", "ENmPqspN");
            Statement stmt = con.createStatement();
        Statement stmt1 = con.createStatement();

            String loan_id_string = pm.getValueAt(row, 0).toString();
            int loan_id = Integer.parseInt(loan_id_string);
             pm = (DefaultTableModel) fineTable2.getModel();
             rst1 = stmt.executeQuery("select fines.loan_id,date_in from book_loans,fines where book_loans.loan_id = fines.loan_id and fines.loan_id = "+loan_id+";");
             while(rst1.next())
             {
                 System.out.println(rst1.getString("date_in"));
                 
                 if(rst1.getString("date_in") == null)
                 
                     JOptionPane.showMessageDialog(null, "It is not possible to pay fine because book havn't been returned","ERROR",JOptionPane.ERROR_MESSAGE);
                
                 else           
                 {
                     stmt1.executeUpdate("update fines set paid = 1 where loan_id = "+loan_id+" ;");
                     JOptionPane.showMessageDialog(null, "Success!","sucess",JOptionPane.INFORMATION_MESSAGE);
                 }
                 

                     
             }
                         
            
              }
        
         catch (SQLException e) {
            System.out.println("Error : " + e.getMessage());
            JOptionPane.showMessageDialog(null, "Invalid input!","ERROR",JOptionPane.ERROR_MESSAGE);

        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
    }
}
