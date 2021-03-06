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
public class LibraryBranchWindow extends javax.swing.JDialog {
    
    public static int addr_length = 80;
    public static int branch_length = 30;

    
    public static String checkApostrophe(String inputString) {
        String str;
        String begin;
        String end;

        str = inputString;
        for (int i = 0; i < inputString.length(); i++) {
            if (inputString.charAt(i) == '\'') {
                begin = inputString.substring(0, i);
                end = inputString.substring(i + 1);
                str = begin + "''" + end;
                break;
            }
        }

        return str;
    }

    /**
     * Creates new form LibraryBranchWindow
     */
    public LibraryBranchWindow(java.awt.Dialog parent, boolean modal) {
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

        OpenFile = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);

        OpenFile.setText("Open File");
        OpenFile.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                OpenFileActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(124, 124, 124)
                .addComponent(OpenFile, javax.swing.GroupLayout.PREFERRED_SIZE, 136, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(140, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(18, 18, 18)
                .addComponent(OpenFile, javax.swing.GroupLayout.PREFERRED_SIZE, 53, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(229, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void OpenFileActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_OpenFileActionPerformed
        JFileChooser fileopen = new JFileChooser();
        FileFilter filter = new FileNameExtensionFilter("Text/CSV file", "txt", "csv");
        fileopen.addChoosableFileFilter(filter);
        fileopen.showOpenDialog(this);
        File file = fileopen.getSelectedFile();
        
        int count = 0;
        try {
            
            Connection conn = null;
            
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/", "root", "ENmPqspN");

            Statement stmt = conn.createStatement();

            stmt.execute("CREATE DATABASE IF NOT EXISTS Library ;");
            stmt.execute("use Library;");

            //if the table already exists --> drop it and then create
            ResultSet rs = stmt.executeQuery("SHOW TABLES LIKE 'LIBRARY_BRANCH';");
            if (rs.next()) {
                stmt.execute("DROP TABLE LIBRARY_BRANCH");
            }

            try ( 
                    BufferedReader reader = new BufferedReader(new FileReader(file))) {
                String line;
                String split_line[];
                String split_author[];
                int branch_id;
                String branch_name;
                String address;

                line = reader.readLine();// Dismiss heading line
                split_line = line.split("\t");
                stmt.execute("CREATE TABLE LIBRARY_BRANCH ( "
                        + "branch_id int NOT NULL PRIMARY KEY, "
                        + "branch_name varchar(" + branch_length + ") NOT NULL,"
                        + "address varchar(" + addr_length + ")) ");

                
                
                while ((line = reader.readLine()) != null) {
                    line = checkApostrophe(line);
                    split_line = line.split("\t");
                    branch_id = Integer.parseInt(split_line[0]);
                    branch_name = split_line[1];
                    address = split_line[2];

                    stmt.execute("INSERT INTO LIBRARY_BRANCH VALUES ('"
                            + branch_id + "','"
                            + branch_name + "','"
                            + address + "');");
                }
            }
            conn.close();
            System.out.println("Library Branch Data loaded");
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
    }//GEN-LAST:event_OpenFileActionPerformed

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
            java.util.logging.Logger.getLogger(LibraryBranchWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(LibraryBranchWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(LibraryBranchWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(LibraryBranchWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the dialog */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                LibraryBranchWindow dialog = new LibraryBranchWindow(new javax.swing.JDialog(), true);
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
    private javax.swing.JButton OpenFile;
    // End of variables declaration//GEN-END:variables
}
