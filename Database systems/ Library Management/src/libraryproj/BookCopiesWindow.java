/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package libraryproj;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 *
 * @author Amin
 */
public class BookCopiesWindow extends javax.swing.JDialog {
    
    public static int book_id_length = 10;
    

    /**
     * Creates new form BookCopiesWindow
     */
    public BookCopiesWindow(java.awt.Dialog parent, boolean modal) {
        super(parent, modal);
        initComponents();
        this.setLocationRelativeTo(null);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        Openfile = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);

        Openfile.setText("Open File");
        Openfile.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                OpenfileActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(165, 165, 165)
                .addComponent(Openfile, javax.swing.GroupLayout.PREFERRED_SIZE, 136, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(166, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(22, 22, 22)
                .addComponent(Openfile, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(260, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void OpenfileActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_OpenfileActionPerformed
        JFileChooser fileopen = new JFileChooser();
        FileFilter filter = new FileNameExtensionFilter("Text/CSV file", "txt", "csv");
        fileopen.addChoosableFileFilter(filter);
        fileopen.showOpenDialog(this);
        File file = fileopen.getSelectedFile();
        
        try {
                    
            Connection conn = null;
            
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/", "root", "ENmPqspN");

            
            Statement stmt = conn.createStatement();
            stmt.execute("CREATE DATABASE IF NOT EXISTS Library ;");
            stmt.execute("use Library;");

            //table already exists --> drop it and then create
            ResultSet rs = stmt.executeQuery("SHOW TABLES LIKE 'BOOK_COPIES';");
            if (rs.next()) {
                stmt.execute("DROP TABLE BOOK_COPIES;");
            }

            try ( 
                BufferedReader reader = new BufferedReader(new FileReader(file))) {
                String line;
                String split_line[]; 
                String book_id;
                int branch_id;
                int no_of_copies;
                line = reader.readLine();// Dismiss header line
                split_line = line.split(",");
                stmt.execute("CREATE TABLE BOOK_COPIES ( "
                        + "book_id varchar(" + book_id_length + ") NOT NULL,"
                        + "branch_id int NOT NULL, "
                        + "no_of_copies int NOT NULL) ");

                while ((line = reader.readLine()) != null) {
                    split_line = line.split(",");
                    book_id = split_line[0];
                    branch_id = Integer.parseInt(split_line[1]);
                    no_of_copies = Integer.parseInt(split_line[2]);
                    stmt.execute("INSERT INTO BOOK_COPIES VALUES ('"
                            + book_id + "','" + branch_id + "','" + no_of_copies + "');");
                }
            }
            conn.close();
            System.out.println("Book Copies Data loaded");
            this.dispose();
        } catch (SQLException ex) {
            System.out.println("Error in connection: " + ex.getMessage());
        } catch (FileNotFoundException ex) {
            JOptionPane.showMessageDialog(null, ex.getMessage());
            ex.printStackTrace();
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, ex.getMessage());
            ex.printStackTrace();
        }
        
        
 
    }//GEN-LAST:event_OpenfileActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(BookCopiesWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(BookCopiesWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(BookCopiesWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(BookCopiesWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the dialog */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                BookCopiesWindow dialog = new BookCopiesWindow(new javax.swing.JDialog(), true);
                dialog.addWindowListener(new java.awt.event.WindowAdapter() {
                    @Override
                    public void windowClosing(java.awt.event.WindowEvent e) {
                        System.exit(0);
                    }
                });
                dialog.setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton Openfile;
    // End of variables declaration//GEN-END:variables
}
