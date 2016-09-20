import java.util.Random;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.List;
import java.util.Map.Entry;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;


public class Kmeans{
    
    public static int k = 25;
    public static String inputfile = "test_data.txt";
    public static String outputfile = "output.txt";


	public static void main(String[] args) throws IOException
    {
        
		
		k = Integer.parseInt(args[0]);
		inputfile = args[1];            //test_data.txt
		outputfile = args[2];           //output.txt

		List<Point> points = loadPoints(inputfile);
		HashMap<Integer, List<Point>> clusterpoint = new HashMap<Integer, List<Point>>();
		List<Point> centroid = new ArrayList<Point>();

		initialize(points, centroid, clusterpoint);
		updatecentroid(centroid, clusterpoint);
		int temp = 1;
		boolean converge;					
		do{
			converge = updateCluster(centroid, clusterpoint);
			temp++;
		}while(temp <= 25 && !converge);
		
		double SSE = totalSse(centroid,clusterpoint);
		System.out.println("SSE for this cluestring : " + SSE);
		writeResult(outputfile, clusterpoint);
	}
    
    
    
    private static List<Point> loadPoints(String inputfile) throws IOException{
        
        BufferedReader r = new BufferedReader(new FileReader(inputfile));
        r.readLine();              //discard header line
        String line;
        List<Point> points = new LinkedList<Point>();
        while ((line = r.readLine()) != null)
        {
            String[] Line = line.split("\t");
            int id = Integer.parseInt(Line[0]);
            float x = Float.parseFloat(Line[1]);
            float y = Float.parseFloat(Line[2]);
            Point entry = new Point(id, x, y);
            points.add(entry);
        }
        return points;
    }
    
    
    public static int randomInt(int min, int max)
    {
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;
        return randomNum;
    }
    
    
    private static void initialize(List<Point> points, List<Point> centroid, HashMap<Integer, List<Point>> clusterpoint)
    {
        
        for (int i = 0; i < k; i++)
        {
            List<Point> cluster = new LinkedList<Point>();
            int random = randomInt(0, points.size() - 1);
            Point p = points.remove(random);
            p.setCluster(i);
            centroid.add(p);
            cluster.add(p);
            clusterpoint.put(i, cluster);
        }
        
        for (Point p : points)
        {
            int nearestcenter = getnearestcenter(p, centroid);
            p.setCluster(nearestcenter);
            clusterpoint.get(nearestcenter).add(p);
        }
    }
    
    
    private static Point computecenter(List<Point> points) {
        float x = 0, y = 0;
        int count = 0;
        for (Point p : points)
        {
            x += p.x;
            y += p.y;
            count++;
        }
        
        x = x / count;
        y = y / count;
        return new Point(-1, x, y);
    }
    



	private static boolean updateCluster(List<Point> centroid, HashMap<Integer, List<Point>> clusterpoint)
    {
		
		boolean converge = true;
		int pointsChangedCount = 0;		
		for (int i = 0; i < k; i++)
        {
			List<Point> points = new ArrayList<Point>(clusterpoint.get(i));
			pointsChangedCount = 0;
			for (Point p : points)
            {
				int nearestcenter = getnearestcenter(p, centroid);
				if (p.cluster != nearestcenter)
                {
					p.setCluster(nearestcenter);
					clusterpoint.get(i).remove(points.indexOf(p)-pointsChangedCount);					
					clusterpoint.get(nearestcenter).add(p);
					converge = false;
					pointsChangedCount++;
				}
			}
		}
		updatecentroid(centroid, clusterpoint);
		return converge;
	}



	private static void updatecentroid(List<Point> centroid, HashMap<Integer, List<Point>> clusterpoint)
    {
		for (int i = 0; i < k; i++)
			centroid.set(i, computecenter(clusterpoint.get(i)));
	}


	public static int getnearestcenter(Point p, List<Point> centroid)
    {
		int nearest = 0;
		double nearestDistance = Double.MAX_VALUE;
		for (int i = 0; i < k; i++)
        {
			double temp = Point.Distance(p, centroid.get(i));
			if (temp < nearestDistance)
            {
				nearest = i;
				nearestDistance = temp;
			}
		}
		return nearest;
	}

    
    private static double totalSse(List<Point> centroid, HashMap<Integer, List<Point>> clusterpoint)
    {
        double SSE = 0;
        for(int i=0;i<k;i++)
        {
            double temp = 0;
            for(Point p :clusterpoint.get(i))
            {
                
                double distance = Point.Distance(p, centroid.get(i));
                distance = distance * distance;
                temp += distance;
            }
            SSE += temp;
        }				
        return SSE;
    }


    
    private static void writeResult(String outputfile, HashMap<Integer, List<Point>> clusterpoint) throws IOException{
        
        File outputFile = new File(outputfile);
        BufferedWriter w = new BufferedWriter(new FileWriter(outputFile));
        
        w.write("Cluster id\tPoints id\n");
        w.write("-------------------------------\n");
        
        for( int i = 0; i < clusterpoint.size(); i++ )
        {
            w.write(i+1 + "\t\t");
            
            for( Point p : clusterpoint.get(i) )
            {
                w.write(p.id + ",");
            }
            w.write("\n");
        }	
        w.close();
    }
    
}
