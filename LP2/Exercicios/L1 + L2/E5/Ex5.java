import javax.swing.JOptionPane;

public class Ex5 extends javax.swing.JApplet {
    MinhaListaOrdenavel lista = new MinhaListaOrdenavel();
    @Override
    public void init() {
        resize(690,380);
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Ex5.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Ex5.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Ex5.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Ex5.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        try {
            java.awt.EventQueue.invokeAndWait(new Runnable() {
                public void run() {
                    initComponents();
                }
            });
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    @SuppressWarnings("unchecked")                   
    private void initComponents() {

        painelGuias = new javax.swing.JTabbedPane();
        abaMenu = new javax.swing.JPanel();
        btnMenuCadastro = new javax.swing.JButton();
        btnMenuTabela = new javax.swing.JButton();
        abaCadastro = new javax.swing.JPanel();
        btnCadastrar = new javax.swing.JButton();
        btnVoltarMenu = new javax.swing.JButton();
        jPanel1 = new javax.swing.JPanel();
        txtFieldNome = new javax.swing.JTextField();
        radioBtnMasc = new javax.swing.JRadioButton();
        radioBtnFem = new javax.swing.JRadioButton();
        labelGeneroExcecao = new javax.swing.JLabel();
        labelAlturaExcecao = new javax.swing.JLabel();
        labelPesoExcecao = new javax.swing.JLabel();
        labelDataNascExcecao = new javax.swing.JLabel();
        labelNomeExcecao = new javax.swing.JLabel();
        formatTxtFieldDataNasc = new javax.swing.JFormattedTextField();
        formatTxtFieldAltura = new javax.swing.JFormattedTextField();
        formatTxtFieldPeso = new javax.swing.JFormattedTextField();
        jPanel2 = new javax.swing.JPanel();
        labelNome = new javax.swing.JLabel();
        labelDataNasc = new javax.swing.JLabel();
        labelAltura = new javax.swing.JLabel();
        labelGenero = new javax.swing.JLabel();
        labelPeso = new javax.swing.JLabel();
        btnVisuTabela = new javax.swing.JButton();
        abaTabela = new javax.swing.JPanel();
        btnVoltarMenu2 = new javax.swing.JButton();
        jScrollPane2 = new javax.swing.JScrollPane();
        tabelaP = new javax.swing.JTable();
        comboBoxOrdena = new javax.swing.JComboBox<>();
        btnCadastro = new javax.swing.JButton();

        btnMenuCadastro.setText("Inserir Pessoas");
        btnMenuCadastro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnMenuCadastroActionPerformed(evt);
            }
        });

        btnMenuTabela.setText("Visualizar Tabela");
        btnMenuTabela.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnMenuTabelaActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout abaMenuLayout = new javax.swing.GroupLayout(abaMenu);
        abaMenu.setLayout(abaMenuLayout);
        abaMenuLayout.setHorizontalGroup(
            abaMenuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(abaMenuLayout.createSequentialGroup()
                .addGap(197, 197, 197)
                .addGroup(abaMenuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(btnMenuTabela, javax.swing.GroupLayout.PREFERRED_SIZE, 200, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnMenuCadastro, javax.swing.GroupLayout.PREFERRED_SIZE, 200, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(350, Short.MAX_VALUE))
        );
        abaMenuLayout.setVerticalGroup(
            abaMenuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(abaMenuLayout.createSequentialGroup()
                .addGap(103, 103, 103)
                .addComponent(btnMenuCadastro, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(btnMenuTabela, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(158, Short.MAX_VALUE))
        );

        painelGuias.addTab("Menu", abaMenu);

        btnCadastrar.setText("Inserir");
        btnCadastrar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCadastrarActionPerformed(evt);
            }
        });

        btnVoltarMenu.setText("Menu");
        btnVoltarMenu.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnVoltarMenuActionPerformed(evt);
            }
        });

        txtFieldNome.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtFieldNomeActionPerformed(evt);
            }
        });

        radioBtnMasc.setText("Masculino");
        radioBtnMasc.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                radioBtnMascActionPerformed(evt);
            }
        });

        radioBtnFem.setText("Feminino");
        radioBtnFem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                radioBtnFemActionPerformed(evt);
            }
        });

        try {
            formatTxtFieldDataNasc.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.MaskFormatter("##/##/####")));
        } catch (java.text.ParseException ex) {
            ex.printStackTrace();
        }

        try {
            formatTxtFieldAltura.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.MaskFormatter("#.##")));
        } catch (java.text.ParseException ex) {
            ex.printStackTrace();
        }

        try {
            formatTxtFieldPeso.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.MaskFormatter("###.##")));
        } catch (java.text.ParseException ex) {
            ex.printStackTrace();
        }

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addComponent(radioBtnMasc)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(radioBtnFem)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(labelGeneroExcecao, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(txtFieldNome, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(formatTxtFieldDataNasc, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(formatTxtFieldAltura, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(formatTxtFieldPeso, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addGap(145, 145, 145)
                                .addComponent(labelAlturaExcecao, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                            .addComponent(labelNomeExcecao, javax.swing.GroupLayout.DEFAULT_SIZE, 353, Short.MAX_VALUE)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addGap(209, 209, 209)
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(labelPesoExcecao, javax.swing.GroupLayout.DEFAULT_SIZE, 144, Short.MAX_VALUE)
                                    .addComponent(labelDataNascExcecao, javax.swing.GroupLayout.DEFAULT_SIZE, 144, Short.MAX_VALUE))))))
                .addGap(0, 0, 0))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(txtFieldNome, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(labelNomeExcecao, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addComponent(formatTxtFieldDataNasc, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(10, 10, 10)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(formatTxtFieldPeso, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                    .addGroup(jPanel1Layout.createSequentialGroup()
                                        .addComponent(formatTxtFieldAltura, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                            .addComponent(radioBtnMasc)
                                            .addComponent(radioBtnFem)))
                                    .addGroup(jPanel1Layout.createSequentialGroup()
                                        .addComponent(labelAlturaExcecao, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(9, 9, 9)
                                        .addComponent(labelGeneroExcecao, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE))))
                            .addComponent(labelPesoExcecao, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addComponent(labelDataNascExcecao, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(21, 21, 21))
        );

        labelNome.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        labelNome.setText("Nome:");

        labelDataNasc.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        labelDataNasc.setText("Data de Nascimento:");

        labelAltura.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        labelAltura.setText("Altura (m):");

        labelGenero.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        labelGenero.setText("Gen??ro:");

        labelPeso.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        labelPeso.setText("Peso (kg):");

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGap(0, 23, Short.MAX_VALUE)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(labelGenero, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(labelNome, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(labelPeso, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(labelAltura, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(labelDataNasc, javax.swing.GroupLayout.Alignment.TRAILING)))
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(labelNome, javax.swing.GroupLayout.PREFERRED_SIZE, 28, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(labelDataNasc, javax.swing.GroupLayout.PREFERRED_SIZE, 28, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(labelPeso, javax.swing.GroupLayout.PREFERRED_SIZE, 28, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(labelAltura, javax.swing.GroupLayout.PREFERRED_SIZE, 28, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(labelGenero, javax.swing.GroupLayout.PREFERRED_SIZE, 28, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        btnVisuTabela.setText("Tabela");
        btnVisuTabela.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnVisuTabelaActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout abaCadastroLayout = new javax.swing.GroupLayout(abaCadastro);
        abaCadastro.setLayout(abaCadastroLayout);
        abaCadastroLayout.setHorizontalGroup(
            abaCadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(abaCadastroLayout.createSequentialGroup()
                .addGroup(abaCadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(abaCadastroLayout.createSequentialGroup()
                        .addGap(72, 72, 72)
                        .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(abaCadastroLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(btnVoltarMenu)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(btnVisuTabela))
                    .addGroup(abaCadastroLayout.createSequentialGroup()
                        .addGap(192, 192, 192)
                        .addComponent(btnCadastrar, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        abaCadastroLayout.setVerticalGroup(
            abaCadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(abaCadastroLayout.createSequentialGroup()
                .addGap(39, 39, 39)
                .addGroup(abaCadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(btnCadastrar, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 32, Short.MAX_VALUE)
                .addGroup(abaCadastroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btnVoltarMenu)
                    .addComponent(btnVisuTabela))
                .addContainerGap())
        );

        painelGuias.addTab("Cadastros", abaCadastro);

        btnVoltarMenu2.setText("Menu");
        btnVoltarMenu2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnVoltarMenu2ActionPerformed(evt);
            }
        });

        tabelaP.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null, null},
                {null, null, null, null, null},
                {null, null, null, null, null},
                {null, null, null, null, null}
            },
            new String [] {
                "Nome", "Data de Nascimento", "Peso (kg)", "Altura (m)", "Resultado IMC"
            }
        ));
        tabelaP.setRowHeight(25);
        jScrollPane2.setViewportView(tabelaP);

        comboBoxOrdena.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "Alfabetica (A-Z)", "Alfabetica (Z-A)", "Menor Peso", "Maior Peso", "Maior Altura", "Menor IMC" }));
        comboBoxOrdena.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboBoxOrdenaActionPerformed(evt);
            }
        });

        btnCadastro.setText("Cadastros");
        btnCadastro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCadastroActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout abaTabelaLayout = new javax.swing.GroupLayout(abaTabela);
        abaTabela.setLayout(abaTabelaLayout);
        abaTabelaLayout.setHorizontalGroup(
            abaTabelaLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 747, Short.MAX_VALUE)
            .addGroup(abaTabelaLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(abaTabelaLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(abaTabelaLayout.createSequentialGroup()
                        .addComponent(btnVoltarMenu2)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(btnCadastro))
                    .addComponent(comboBoxOrdena, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(587, Short.MAX_VALUE))
        );
        abaTabelaLayout.setVerticalGroup(
            abaTabelaLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(abaTabelaLayout.createSequentialGroup()
                .addGap(29, 29, 29)
                .addComponent(comboBoxOrdena, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 148, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 103, Short.MAX_VALUE)
                .addGroup(abaTabelaLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btnVoltarMenu2)
                    .addComponent(btnCadastro))
                .addContainerGap())
        );

        painelGuias.addTab("Tabela", abaTabela);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(painelGuias)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(painelGuias)
        );
    }                     

    private void btnMenuCadastroActionPerformed(java.awt.event.ActionEvent evt) {                                                
        painelGuias.setSelectedIndex(1);
    }                                               

    private void btnMenuTabelaActionPerformed(java.awt.event.ActionEvent evt) {                                              
        painelGuias.setSelectedIndex(2);
    }                                             

    private void btnVoltarMenu2ActionPerformed(java.awt.event.ActionEvent evt) {                                               
        painelGuias.setSelectedIndex(0);
    }                                              

    private void btnVoltarMenuActionPerformed(java.awt.event.ActionEvent evt) {                                              
        painelGuias.setSelectedIndex(0);
    }                                             

    private void txtFieldNomeActionPerformed(java.awt.event.ActionEvent evt) {                                             
    }                                            

    private void inserir(){
        String tab[][] = new String[lista.getSize()][6];
        
        for(int i = 0; i < lista.getSize(); i++){
            tab[i][0] = lista.getArray(i).getNome();
            tab[i][1] = lista.getArray(i).getData();
            tab[i][2] = Double.toString(lista.getArray(i).getPeso());
            tab[i][3] = Double.toString(lista.getArray(i).getAltura());
            tab[i][4] = lista.getArray(i).resultIMC();
        }
        tabelaP.setModel(new javax.swing.table.DefaultTableModel(
            tab,
            new String [] {
                "Nome", "Data de Nascimento", "Peso", "Altura", "Resultado IMC"
            }
        ));
        painelGuias.setSelectedIndex(0);
        JOptionPane.showMessageDialog(null, "Inserido com sucesso!!");
    }
        
    public boolean isDouble(String str){
        try{
            Double.parseDouble(str);
            return true;
        }catch(NumberFormatException e){
            return false;
        }  
    }
    
    private void btnCadastrarActionPerformed(java.awt.event.ActionEvent evt) {                                             
        // TODO add your handling code here:
        final boolean editValid = formatTxtFieldDataNasc.isEditValid();
        if("".equals(txtFieldNome.getText())){
            JOptionPane.showMessageDialog(null, "Digite algum nome.");
        }else if(!editValid){
            JOptionPane.showMessageDialog(null, "Digite uma data de nascimento.");
        }else if(!isDouble(formatTxtFieldPeso.getText())){
            JOptionPane.showMessageDialog(null, "O peso digitado n??o ?? v??lido.");
        }else if(!isDouble(formatTxtFieldAltura.getText())){
            JOptionPane.showMessageDialog(null, "A altura digitado n??o ?? valido.");
        }else if(!radioBtnMasc.isSelected() && !radioBtnFem.isSelected()){
            JOptionPane.showMessageDialog(null, "Escolha um dos gen??ros.");
        }else{
            double peso = Double.parseDouble(formatTxtFieldPeso.getText());
            double altura = Double.parseDouble(formatTxtFieldAltura.getText());
            if(peso < 5 || peso > 250){
                JOptionPane.showMessageDialog(null, "O peso digitado n??o ?? valido.");
            }else if(altura < 0 || altura > 3.00){
                JOptionPane.showMessageDialog(null, "A altura digitada n??o ?? v??lida.");
            }else{
                if(radioBtnMasc.isSelected()){
                    lista.add(new Homem(txtFieldNome.getText(), formatTxtFieldDataNasc.getText(), peso, altura));
                }else if(radioBtnFem.isSelected()){
                    lista.add(new Mulher(txtFieldNome.getText(), formatTxtFieldDataNasc.getText(), peso, altura));
                }
                inserir();
                labelNomeExcecao.setText("");
                labelDataNascExcecao.setText("");
                labelGeneroExcecao.setText("");
                labelPesoExcecao.setText("");
                labelAlturaExcecao.setText("");
                txtFieldNome.setText("");
                formatTxtFieldDataNasc.setText("");
                formatTxtFieldPeso.setText("");
                formatTxtFieldAltura.setText("");
                radioBtnMasc.setSelected(false);
                radioBtnFem.setSelected(false);
            }
        }
    }                                            

    
    private void radioBtnMascActionPerformed(java.awt.event.ActionEvent evt) {                                             
        if(radioBtnMasc.isSelected()){
            radioBtnFem.setSelected(false);
        }
    }                                            

    private void radioBtnFemActionPerformed(java.awt.event.ActionEvent evt) {                                            
        if(radioBtnFem.isSelected()){
            radioBtnMasc.setSelected(false);
        }
    }                                           

    private void comboBoxOrdenaActionPerformed(java.awt.event.ActionEvent evt) {                                               
        int opcaoOrd = comboBoxOrdena.getSelectedIndex();
        opcaoOrd++;
        lista.ordena(opcaoOrd);
        String tab[][] = new String[lista.getSize()][6];
        
        for(int i = 0; i < lista.getSize(); i++){
            tab[i][0] = lista.getArray(i).getNome();
            tab[i][1] = lista.getArray(i).getData();
            tab[i][2] = Double.toString(lista.getArray(i).getPeso());
            tab[i][3] = Double.toString(lista.getArray(i).getAltura());
            tab[i][4] = lista.getArray(i).resultIMC();
        }
        tabelaP.setModel(new javax.swing.table.DefaultTableModel(
            tab,
            new String [] {
                "Nome", "Data de Nascimento", "Peso", "Altura", "Resultado IMC"
            }
        ));
    }                                              

    private void btnCadastroActionPerformed(java.awt.event.ActionEvent evt) {                                            
        painelGuias.setSelectedIndex(1);
    }                                           

    private void btnVisuTabelaActionPerformed(java.awt.event.ActionEvent evt) {                                              
        painelGuias.setSelectedIndex(2);
    }                                             

          
    private javax.swing.JPanel abaCadastro;
    private javax.swing.JPanel abaMenu;
    private javax.swing.JPanel abaTabela;
    private javax.swing.JButton btnCadastrar;
    private javax.swing.JButton btnCadastro;
    private javax.swing.JButton btnMenuCadastro;
    private javax.swing.JButton btnMenuTabela;
    private javax.swing.JButton btnVisuTabela;
    private javax.swing.JButton btnVoltarMenu;
    private javax.swing.JButton btnVoltarMenu2;
    private javax.swing.JComboBox<String> comboBoxOrdena;
    private javax.swing.JFormattedTextField formatTxtFieldAltura;
    private javax.swing.JFormattedTextField formatTxtFieldDataNasc;
    private javax.swing.JFormattedTextField formatTxtFieldPeso;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JLabel labelAltura;
    private javax.swing.JLabel labelAlturaExcecao;
    private javax.swing.JLabel labelDataNasc;
    private javax.swing.JLabel labelDataNascExcecao;
    private javax.swing.JLabel labelGenero;
    private javax.swing.JLabel labelGeneroExcecao;
    private javax.swing.JLabel labelNome;
    private javax.swing.JLabel labelNomeExcecao;
    private javax.swing.JLabel labelPeso;
    private javax.swing.JLabel labelPesoExcecao;
    private javax.swing.JTabbedPane painelGuias;
    private javax.swing.JRadioButton radioBtnFem;
    private javax.swing.JRadioButton radioBtnMasc;
    private javax.swing.JTable tabelaP;
    private javax.swing.JTextField txtFieldNome;             
}