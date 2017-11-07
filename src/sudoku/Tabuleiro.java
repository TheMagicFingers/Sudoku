package sudoku;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.util.Random;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;

public class Tabuleiro extends JPanel{
    public static final int GRID_ROWS = 1;
    public static final int GRID_COLUMNS = 1;
    public static final int BOARD_ROWS = 9;
    public static final int BOARD_COLUMNS = 9;
    public static JTextField fields[][];

    public Tabuleiro() {
        setBorder(new EmptyBorder(4, 4, 4, 4));
        fields = new JTextField[GRID_ROWS * BOARD_ROWS][GRID_COLUMNS * BOARD_COLUMNS];

        setLayout(new GridLayout(GRID_ROWS, GRID_COLUMNS, 2, 2));
        add(createBoard(fields, 0, 0));

    }

    public JPanel createBoard(JTextField fiels[][], int startRow, int startCol) {
        JPanel panel = new JPanel(new GridLayout(3, 3, 2, 2));
        panel.setBorder(new CompoundBorder(new LineBorder(Color.BLACK, 2), new EmptyBorder(2, 2, 2, 2)));

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                int rowIndex = (startRow + row) * 3;
                int colIndex = (startCol + col) * 3;
                panel.add(createSubBoard(fields, rowIndex, colIndex));
            }
        }
        return panel;
    }

    protected JPanel createSubBoard(JTextField[][] fields, int startRow, int startCol) {
        JPanel panel = new JPanel(new GridLayout(3, 3, 2, 2));
        panel.setBorder(new CompoundBorder(new LineBorder(Color.GRAY, 2), new EmptyBorder(2, 2, 2, 2)));

        populateFields(fields, startRow, startCol);
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                panel.add(fields[row + startRow][col + startCol]);
            }
        }
        return panel;
    }
    
    protected void populateFields(JTextField[][] fields, int startRow, int startCol) {
        Font font = new Font("SansSerif", Font.BOLD, 20);
        for (int row = startRow; row < startRow + 3; row++) {
            for (int col = startCol; col < startCol + 3; col++) {
                
                Random gerador = new Random();
                int numRandom = 0;
                int modRandomx = 0;
                int modRandomy = 0;
                while(numRandom == 0){
                    numRandom = gerador.nextInt(10);
                    modRandomx = gerador.nextInt(4);
                    modRandomy = gerador.nextInt(4);
                }
                
                JTextField campo = new JTextField(1);
                campo.setHorizontalAlignment(JTextField.CENTER);
                campo.setFont(font);
                
                if(row % 2 == modRandomx && col % 3 == modRandomy){
                    campo.setText(Integer.toString(numRandom));
                }
                fields[row][col] = campo;
            }
        }
    }
}
