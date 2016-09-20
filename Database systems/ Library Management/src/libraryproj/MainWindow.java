package libraryproj;

import javax.swing.table.DefaultTableModel;

/**
 *
 * @author Amin
 */
public class MainWindow extends javax.swing.JFrame {

    public MainWindow() {

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

        jPanel1 = new javax.swing.JPanel();
        searchButton = new javax.swing.JButton();
        checkoutButton = new javax.swing.JButton();
        titleLabel = new javax.swing.JLabel();
        checkinButton = new javax.swing.JButton();
        borrowerButton = new javax.swing.JButton();
        paymentButton = new javax.swing.JButton();
        jSeparator1 = new javax.swing.JSeparator();
        jSeparator2 = new javax.swing.JSeparator();
        UploadButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);

        jPanel1.setMinimumSize(new java.awt.Dimension(39, 39));
        jPanel1.setPreferredSize(new java.awt.Dimension(1000, 1000));
        jPanel1.setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        searchButton.setFont(new java.awt.Font("Lucida Grande", 3, 14)); // NOI18N

        searchButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/libraryproj/icon/1436869024_xmag.png"))); // NOI18N
        searchButton.setText("Search");
        searchButton.setIconTextGap(23);
        searchButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchButtonActionPerformed(evt);
            }
        });
        jPanel1.add(searchButton, new org.netbeans.lib.awtextra.AbsoluteConstraints(50, 10, 200, 70));

        checkoutButton.setFont(new java.awt.Font("Lucida Grande", 3, 14)); // NOI18N
        checkoutButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/libraryproj/icon/add-to-cart-dark.png"))); // NOI18N
        checkoutButton.setText("Check out");
        checkoutButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                checkoutButtonActionPerformed(evt);
            }
        });
        jPanel1.add(checkoutButton, new org.netbeans.lib.awtextra.AbsoluteConstraints(50, 80, 200, 70));
        jPanel1.add(titleLabel, new org.netbeans.lib.awtextra.AbsoluteConstraints(50, 30, 190, -1));

        checkinButton.setFont(new java.awt.Font("Lucida Grande", 3, 14)); // NOI18N
        checkinButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/libraryproj/icon/remove-from-cart-dark.png"))); // NOI18N
        checkinButton.setText("Check in");
        checkinButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                checkinButtonActionPerformed(evt);
            }
        });
        jPanel1.add(checkinButton, new org.netbeans.lib.awtextra.AbsoluteConstraints(50, 150, 200, 70));

        borrowerButton.setFont(new java.awt.Font("Lucida Grande", 3, 14)); // NOI18N
        borrowerButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/libraryproj/icon/1436868545_user-group-new.png"))); // NOI18N
        borrowerButton.setText("New borrower");
        borrowerButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                borrowerButtonActionPerformed(evt);
            }
        });
        jPanel1.add(borrowerButton, new org.netbeans.lib.awtextra.AbsoluteConstraints(50, 220, 200, 70));

        paymentButton.setFont(new java.awt.Font("Lucida Grande", 3, 14)); // NOI18N
        paymentButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/libraryproj/icon/1436869666_cash_register.png"))); // NOI18N
        paymentButton.setText("Fines");
        paymentButton.setIconTextGap(30);
        paymentButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                paymentButtonActionPerformed(evt);
            }
        });
        jPanel1.add(paymentButton, new org.netbeans.lib.awtextra.AbsoluteConstraints(50, 290, 200, 70));
        jPanel1.add(jSeparator1, new org.netbeans.lib.awtextra.AbsoluteConstraints(120, 230, -1, -1));
        jPanel1.add(jSeparator2, new org.netbeans.lib.awtextra.AbsoluteConstraints(180, 170, -1, -1));

        UploadButton.setText("Upload Data");
        UploadButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                UploadButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(UploadButton, javax.swing.GroupLayout.PREFERRED_SIZE, 135, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 168, Short.MAX_VALUE)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, 377, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(UploadButton, javax.swing.GroupLayout.PREFERRED_SIZE, 33, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void searchButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_searchButtonActionPerformed
        Searchbookwindow sw = new Searchbookwindow(this, true);
        sw.setVisible(true);
    }//GEN-LAST:event_searchButtonActionPerformed

    private void checkoutButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_checkoutButtonActionPerformed
        Checkoutwindow cw = new Checkoutwindow(this, true);
        cw.setVisible(true);
    }//GEN-LAST:event_checkoutButtonActionPerformed

    private void checkinButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_checkinButtonActionPerformed
        Checkinwindow cinw = new Checkinwindow(this, true);
        cinw.setVisible(true);
    }//GEN-LAST:event_checkinButtonActionPerformed

    private void borrowerButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_borrowerButtonActionPerformed
        Newbrwindow bw = new Newbrwindow(this, true);
        bw.setVisible(true);
    }//GEN-LAST:event_borrowerButtonActionPerformed

    private void paymentButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_paymentButtonActionPerformed
        Paymentwindow pw = new Paymentwindow(this, true);
        pw.setVisible(true);
    }//GEN-LAST:event_paymentButtonActionPerformed

    private void UploadButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_UploadButtonActionPerformed
        Uploadwindow uw = new Uploadwindow(this, true);
        uw.setVisible(true);
    }//GEN-LAST:event_UploadButtonActionPerformed

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
            java.util.logging.Logger.getLogger(MainWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(MainWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(MainWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(MainWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new MainWindow().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton UploadButton;
    private javax.swing.JButton borrowerButton;
    private javax.swing.JButton checkinButton;
    private javax.swing.JButton checkoutButton;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JSeparator jSeparator2;
    private javax.swing.JButton paymentButton;
    private javax.swing.JButton searchButton;
    private javax.swing.JLabel titleLabel;
    // End of variables declaration//GEN-END:variables
}