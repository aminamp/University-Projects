package libraryproj;



/**
 *
 * @author Amin
 */
public class Uploadwindow extends javax.swing.JDialog {

   
    public Uploadwindow(java.awt.Frame parent, boolean modal) {
        super(parent, modal);
        initComponents();
        this.setLocationRelativeTo(null);
    }

    /**
     * This method is called from within the constructor to initialize the form. WARNING: Do NOT modify this code. The content of this method is always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        librarybranch = new javax.swing.JButton();
        borrower = new javax.swing.JButton();
        bookcopies = new javax.swing.JButton();
        booksauthors = new javax.swing.JButton();
        Bookloans = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setResizable(false);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        jPanel1.setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        librarybranch.setText("Library Branch Data");
        librarybranch.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                librarybranchActionPerformed(evt);
            }
        });
        jPanel1.add(librarybranch, new org.netbeans.lib.awtextra.AbsoluteConstraints(30, 190, 220, 60));

        borrower.setText("Borrowers Data");
        borrower.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                borrowerActionPerformed(evt);
            }
        });
        jPanel1.add(borrower, new org.netbeans.lib.awtextra.AbsoluteConstraints(30, 130, 220, 60));

        bookcopies.setText("Book Copies Data");
        bookcopies.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bookcopiesActionPerformed(evt);
            }
        });
        jPanel1.add(bookcopies, new org.netbeans.lib.awtextra.AbsoluteConstraints(30, 10, 220, 60));

        booksauthors.setText("Books Authors Data");
        booksauthors.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                booksauthorsActionPerformed(evt);
            }
        });
        jPanel1.add(booksauthors, new org.netbeans.lib.awtextra.AbsoluteConstraints(30, 70, 220, 60));

        Bookloans.setText("Book Loans");
        Bookloans.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BookloansActionPerformed(evt);
            }
        });
        jPanel1.add(Bookloans, new org.netbeans.lib.awtextra.AbsoluteConstraints(30, 250, 220, 60));

        getContentPane().add(jPanel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 290, 320));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void borrowerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_borrowerActionPerformed
        BorrowersWindow lbw = new BorrowersWindow(this, true);
        lbw.setVisible(true);
    }//GEN-LAST:event_borrowerActionPerformed

    private void librarybranchActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_librarybranchActionPerformed
        LibraryBranchWindow lbw = new LibraryBranchWindow(this, true);
        lbw.setVisible(true);
    }//GEN-LAST:event_librarybranchActionPerformed

    private void bookcopiesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bookcopiesActionPerformed
        BookCopiesWindow bcw = new BookCopiesWindow(this, true);
        bcw.setVisible(true);
    }//GEN-LAST:event_bookcopiesActionPerformed

    private void booksauthorsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_booksauthorsActionPerformed
        
        BookAuthorsWindow baw = new BookAuthorsWindow(this, true);
        baw.setVisible(true);
    }//GEN-LAST:event_booksauthorsActionPerformed

    private void BookloansActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BookloansActionPerformed
        BookLoans bl = new BookLoans(this, true);
        bl.setVisible(true);
    }//GEN-LAST:event_BookloansActionPerformed

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
            java.util.logging.Logger.getLogger(Uploadwindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Uploadwindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Uploadwindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Uploadwindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>

        /* Create and display the dialog */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                Uploadwindow dialog = new Uploadwindow(new javax.swing.JFrame(), true);
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
    private javax.swing.JButton Bookloans;
    private javax.swing.JButton bookcopies;
    private javax.swing.JButton booksauthors;
    private javax.swing.JButton borrower;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JButton librarybranch;
    // End of variables declaration//GEN-END:variables
}
