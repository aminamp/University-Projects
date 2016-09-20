
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *
 * @author Amin
 */
public class test {


    public static void main(String[] args) {
        
        FileWriter fw= null;
        try {
            String filename= "MLResult.txt";
            File file = new File(filename);
            fw = new FileWriter(filename);
            fw.write("");   //clear previous result
            fw.close();
            for(int round = 1; round <= 5; round++ )
            {
                FileWriter aw = new FileWriter(filename, true);
                aw.write(String.format("Round %d: \n", round));
                aw.write(String.format("%s %20s %20s \r\n", "Strategy", "Number of games", "Ending Balance"));
                aw.close();
                EvenWager(filename);
                MartingaleSystem(filename);
                ReverseMartingaleSystem(filename);   
            }
        } catch (IOException ex) {
            Logger.getLogger(test.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                fw.close();
            } catch (IOException ex) {
                Logger.getLogger(test.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
  
    }
    
    
    public static void EvenWager(String filename) throws IOException
    {
         
        SecureRandom randomNumber = new SecureRandom();
        int wager = 100;
        int balance = 1000;
        int counter;

        for( counter = 1; counter <= 10; counter++ )
        {
			int dice1 = 1 + randomNumber.nextInt(6); //pick random integer from 1 to 6
                        int dice2 = 1 + randomNumber.nextInt(6);
                        int sum = dice1 + dice2;
                        int point;
                        

                        if ( sum == 7 || sum == 11)
                            balance = balance + wager;

                        else if ( sum == 2 || sum == 3 || sum == 12)
                            balance = balance - wager;

                        else
                        {
                            point = sum;
                            for( ; ; )
                            {
                                dice1 = 1 + randomNumber.nextInt(6);
                                dice2 = 1 + randomNumber.nextInt(6);
                                sum = dice1 + dice2;
                                if( sum == point )
                                {
                                    balance = balance + wager;
                                    break;
                                }
                                else if ( sum == 7 )
                                {
                                    balance = balance - wager;
                                    break;
                                }
                                    
                            }//end of for( ; ; )
                            
                        }
                            
	}//end of outer for
        
        FileWriter aw = new FileWriter(filename, true);
        aw.write(String.format("%4s %18d %21d \n", "1", counter - 1 , balance));
        aw.close();

    }
    
    
    public static void MartingaleSystem(String filename) throws IOException
    {
         
        SecureRandom randomNumber = new SecureRandom();
        int wager = 100;
        int balance = 1000;
        int counter;

        for( counter = 1; counter <= 10; ++counter )
        {
			int dice1 = 1 + randomNumber.nextInt(6); //pick random integer from 1 to 6
                        int dice2 = 1 + randomNumber.nextInt(6);
                        int sum = dice1 + dice2;
                        int point;
                        int temp = 0;

                        if ( sum == 7 || sum == 11)
                        {
                            balance = balance + wager;
                            wager = 100;
                        }
                            
                        else if ( sum == 2 || sum == 3 || sum == 12)
                        {
                            balance = balance - wager;
                            if( balance == 0 )
                                break;
                            wager = wager * 2;
                            if( wager > balance )
                                wager = balance;
                        }

                        else
                        {
                            point = sum;
                            for( ; ; )
                            {
                                dice1 = 1 + randomNumber.nextInt(6);
                                dice2 = 1 + randomNumber.nextInt(6);
                                sum = dice1 + dice2;
                                
                                if( sum == point )
                                {
                                    balance = balance + wager;
                                    wager = 100;
                                    break;
                                }
                                else if ( sum == 7 )
                                {
                                    balance = balance - wager;
                                    if( balance == 0 )
                                        temp = 1;
                                    wager = wager * 2;
                                    if( wager > balance )
                                         wager = balance;
                                    break;
                                }
                                    
                            }//end of for( ; ; )
                            if( temp == 1)
                                break;
                            
                        }
                            
	}//end of outer for
        if(counter == 11)
            counter -= 1; 
        
        FileWriter aw = new FileWriter(filename, true);
        aw.write(String.format("%4s %18d %21d \n", "2", counter, balance));
        aw.close();
    }
    
        public static void ReverseMartingaleSystem(String filename) throws IOException
    {
         
        SecureRandom randomNumber = new SecureRandom();
        int wager = 100;
        int balance = 1000;
        int counter;

        for( counter = 1; counter <= 10; ++counter )
        {
			int dice1 = 1 + randomNumber.nextInt(6); //pick random integer from 1 to 6
                        int dice2 = 1 + randomNumber.nextInt(6);
                        int sum = dice1 + dice2;
                        int point;
                        int temp = 0;
                        
                        if ( sum == 7 || sum == 11)
                        {
                            balance = balance + wager;
                            wager = wager * 2;
                            if( wager > balance )
                                wager = balance;
                        }
                            
                        else if ( sum == 2 || sum == 3 || sum == 12)
                        {
                            balance = balance - wager;
                            if( balance == 0 )
                                break;
                            wager = 100;
                        }

                        else
                        {
                            point = sum;
                            for( ; ; )
                            {
                                dice1 = 1 + randomNumber.nextInt(6);
                                dice2 = 1 + randomNumber.nextInt(6);
                                sum = dice1 + dice2;
                                if( sum == point )
                                {
                                    balance = balance + wager;
                                    wager = wager * 2;
                                    if( wager > balance )
                                         wager = balance;

                                    break;
                                }
                                else if ( sum == 7 )
                                {
                                    balance = balance - wager;
                                    if( balance == 0 )
                                        temp = 1;
                                    wager = 100;

                                    break;
                                }
                                    
                            }//end of for( ; ; )
                            if( temp == 1)
                                break;
                            
                        }
                            
	}//end of outer for
        if(counter == 11)
            counter -= 1; 
        
        FileWriter aw = new FileWriter(filename, true);
        aw.write(String.format("%4s %18d %21d \n\n\n", "3", counter, balance));
        aw.close();
    }
}
