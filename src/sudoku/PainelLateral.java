/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

/**
 *
 * @author gustavo
 */

public class PainelLateral extends JPanel{
    public PainelLateral() {
            setBorder(new EmptyBorder(4, 4, 3, 3));
            setLayout(new GridBagLayout());
            GridBagConstraints gbc = new GridBagConstraints();
            gbc.gridx = 0;
            gbc.gridy = 1;
            gbc.weightx = 1;
            gbc.fill = GridBagConstraints.HORIZONTAL;

            JButton novo = new JButton("Novo");
            JButton checar = new JButton("Checar");
            JButton sair = new JButton("Sair");
            
            add(novo, gbc);
            gbc.gridy++;
            add(checar, gbc);
            gbc.gridy++;
            add(sair, gbc);
            
            novo.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int certeza = JOptionPane.showConfirmDialog(null, "Todo conteúdo da sessão atual será apagado.\nDeseja realmente apagar?", "Novo Jogo", JOptionPane.YES_NO_OPTION);
                    if(certeza == JOptionPane.YES_OPTION){
                        try{
                            FileWriter out = new FileWriter("matriz.txt");
                            out.write("");
                            out.close();
                        }catch(IOException err){
                            System.out.println(err.getMessage());
                        }
                        for(JTextField[] t : Tabuleiro.fields){
                            for(JTextField campo : t){
                                campo.setText("");
                            }
                        }
                    }
                }
            });
            
            checar.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    try {
                        FileWriter out = new FileWriter(System.getProperty("user.dir")+"/matriz.txt");
                        out.write("");
                        for(JTextField[] t : Tabuleiro.fields){
                            for(JTextField campo : t){
                                out.append(campo.getText() + " ");
                            }
                            out.append("\n");
                        }
                        out.close();
                        Runtime.getRuntime().exec(System.getProperty("user.dir")+"/checker");
                        
                        BufferedReader bf = new BufferedReader(new FileReader("resposta.txt"));
                        JOptionPane.showMessageDialog(null, bf.readLine());
                    } catch (IOException ex) {
                        System.out.println("Erro.");
                    }     
                }
            });
            
            sair.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    
                }
            });
        }
}
