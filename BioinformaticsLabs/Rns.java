import java.io.*;
import java.util.ArrayList;
public class Rns {
	public static String[] arr(String dna, int k) {
		ArrayList<String> parts = new ArrayList<String>();
		for (int i = 0; i <= dna.length() - k; i+=k) {
			parts.add(dna.substring(i, i + k));
		}
		return parts.toArray(new String[parts.size()]);
	}
	public static String rnaToMole(String rna) {
		String mole = "";
		String[] strand = arr(rna, 3);
		for (String s : strand) {
			String p = "";
			for (int i = 0; i < s.length(); i++) {
				p += s.charAt(i);
			}
			String b = p.substring(0, 2);
			switch(b) {
			case "CA":
				char j = p.charAt(2);
				switch(j) {
				case 'U':
					mole += 'H';
					break;
				case 'C':
					mole += 'H';
					break;
				default:
					mole += 'Q';
					break;
				}
				break;
			case "CC":
				mole += 'P';
				break;
			case "CG":
				mole += 'R';
				break;
			case "CU":
				mole += 'L';
				break;
			case "GA":
				char k = p.charAt(2);
				switch(k) {
				case 'U':
					mole += 'D';
					break;
				case 'C':
					mole += 'D';
					break;
				default:
					mole += 'E';
					break;
				}
				break;
			case "GC":
				mole += 'A';
				break;
			case "GG":
				mole += 'G';
				break;
			case "GU":
				mole += 'V';
				break;
			case "UA":
				char m = p.charAt(2);
				switch(m) {
				case 'U':
					mole += 'Y';
					break;
				case 'C':
					mole += 'Y';
					break;
				default:
					break;
				}
				break;
			case "UC":
				mole += 'S';
				break;
			case "UG":
				char n = p.charAt(2);
				switch(n) {
				case 'U':
					mole += 'C';
					break;
				case 'C':
					mole += 'C';
					break;
				case 'G':
					mole += 'W';
					break;
				default:
					break;
				}
				break;
			case "UU":
				char a = p.charAt(2);
				switch(a) {
				case 'U':
					mole += 'F';
					break;
				case 'C':
					mole += 'F';
					break;
				default:
					mole += 'L';
					break;
				}
				break;
			case "AA":
				char o = p.charAt(2);
				switch(o) {
				case 'U':
					mole += 'N';
					break;
				case 'C':
					mole += 'N';
					break;
				default:
					mole += 'K';
					break;
				}
				break;
			case "AC":
				mole += 'T';
				break;
			case "AG":
				char q = p.charAt(2);
				switch(q) {
				case 'U':
					mole += 'S';
					break;
				case 'C':
					mole += 'S';
					break;
				default:
					mole += 'R';
					break;
				}
				break;
			case "AU":
				char t = p.charAt(2);
				switch(t) {
				case 'G':
					mole += 'M';
					break;
				default:
					mole += 'I';
					break;
				}
			break;
		}
		}
		return mole;
	}
	public static void main(String[] args) {

        String fileName = "LongString.txt";


        String line = "";
        
        String text = "";

        try {

            FileReader fileReader = 
                new FileReader(fileName);


            BufferedReader bufferedReader = 
                new BufferedReader(fileReader);

            while((line = bufferedReader.readLine()) != null) {
               //System.out.println(line);
               text += line;
            }   

            // Always close files.
            bufferedReader.close();         
        }
        catch(FileNotFoundException ex) {
            System.out.println("Unable to open file " + fileName + "!");                
        }
        catch(IOException ex) {
            System.out.println("Error reading file " + fileName + "!");
        }
		String s = "AUGCCCAUGGGAAUU";
		String e = text.substring(0, s.length());
		String subt = "GCGTTCCGAACCACTTTCTGGTACT";
		String[] breaks = arr(text, 3);
		for (int i = 0; i < breaks.length; i++) {
			//System.out.println(breaks[i]);
		}
		//System.out.println(rnaToMole(e));
		System.out.println(rnaToMole(text));
	}
}