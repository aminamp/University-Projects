import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.*;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;



public class TweetsKMeans
{

	public static int k = 25;
	public static String inputfile = "Tweets.json";
	public static String InitialCenter = "InitialCenter.txt";
	public static String output = "output.txt";

	public static void main(String[] args) throws IOException
    {
		
		k = Integer.parseInt(args[0]);
		InitialCenter = args[1];
		inputfile = args[2];
		output = args[3];
		
		HashSet<String> initialSeeds = readInitialSeeds(InitialCenter);
		List<Tweet> centroids = new ArrayList<Tweet>();		
		List<Tweet> tweets = readFile(inputfile,centroids,initialSeeds);		
		HashMap<Integer, List<Tweet>> clusterPoints = new HashMap<Integer, List<Tweet>>();
		
		
		initialize(tweets, centroids, clusterPoints);						
		updatecenter(centroids, clusterPoints);
		int temp = 1;
		boolean converge;					
		do{
			converge = updateCluster(centroids, clusterPoints);
			temp++;
		}
		while(temp <= 25 && !converge);
					
		double SSE = totalSse(centroids,clusterPoints);
		System.out.println("SSE for this clustering : " + SSE);
		writeResult(output, clusterPoints);
	}
	
    
    
    public static int randomInt(int min, int max)
    {
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;
        return randomNum;
    }
    
    private static void initialize(List<Tweet> tweets, List<Tweet> centroids, HashMap<Integer, List<Tweet>> clusterPoints)
    {
        
        for (int i = 0; i < k; i++) {
            List<Tweet> cluster = new LinkedList<Tweet>();
            Tweet t = centroids.get(i);
            t.setCluster(i);
            cluster.add(t);
            clusterPoints.put(i, cluster);
        }
        for (Tweet tweet : tweets)
        {
            int nearestCentroid = getNearestCentroid(tweet, centroids);
            tweet.setCluster(nearestCentroid);
            clusterPoints.get(nearestCentroid).add(tweet);
        }
    }


	private static HashSet<String> readInitialSeeds(String InitialCenter) throws IOException
    {
		HashSet<String> initialSeeds = new HashSet<String>();		
		BufferedReader reader = new BufferedReader(new FileReader(InitialCenter));
		
		while(true)
        {
			String line = reader.readLine();
			if(line == null)
            {
				break;
			}
			initialSeeds.add(line.replace(",", ""));
		}
		return initialSeeds;
	}
    
    
    private static List<Tweet> readFile(String inputfile, List<Tweet> centroids, HashSet<String> initialSeeds)
    throws IOException {
        
        List<Tweet> tweets = new LinkedList<Tweet>();
        JsonParser parser = new JsonParser();
        BufferedReader reader = new BufferedReader(new FileReader(inputfile));
        
        while(true)
        {
            String line = reader.readLine();
            if(line == null)
                break;
            JsonObject object = parser.parse(line).getAsJsonObject();
            Tweet tweet = new Tweet(object.get("id").toString(), object.get("text").toString().replace("\"", ""));
            if(initialSeeds.contains(object.get("id").toString()))
            {
                centroids.add(tweet);
                continue;
            }
            tweets.add(tweet);			
        }	
        return tweets;
    }



	private static boolean updateCluster(List<Tweet> centroids,HashMap<Integer, List<Tweet>> clusterPoints)
    {
		
		boolean converge = true;
		int pointsChangedCount = 0;		
		
		for (int i = 0; i < k; i++)
        {
			
			List<Tweet> tweets = new ArrayList<Tweet>(clusterPoints.get(i));
			pointsChangedCount = 0;
			for (Tweet tweet : tweets)
            {
				int nearestCentroid = getNearestCentroid(tweet, centroids);				
				if (tweet.cluster != nearestCentroid)
                {
					tweet.setCluster(nearestCentroid);
					clusterPoints.get(i).remove(tweets.indexOf(tweet)-pointsChangedCount);					
					clusterPoints.get(nearestCentroid).add(tweet);
					converge = false;
					pointsChangedCount++;
				}
			}
		}
		updatecenter(centroids, clusterPoints);
		return converge;
	}



	private static void updatecenter(List<Tweet> centroids, HashMap<Integer, List<Tweet>> clusterPoints)
    {
		for (int i = 0; i < k; i++)
			centroids.set(i, computecenter(clusterPoints.get(i)));
	}

	private static Tweet computecenter(List<Tweet> list)
    {
		
		float minAverageDist = Float.MAX_VALUE;
		Tweet minAverageDistTweet = null;
		
		for(Tweet tweet1 : list)
        {
			float temp = 0;
			for(Tweet tweet2 : list)
            {
				temp += Tweet.distance(tweet1, tweet2);
			}
			
			if(temp < minAverageDist){
				minAverageDist = temp;
				minAverageDistTweet = tweet1;
			}
		}		
		return minAverageDistTweet;		
	}
	
	public static int getNearestCentroid(Tweet tweet, List<Tweet> centroids)
    {
		int nearest = 0;
		float nearestDistance = Float.MAX_VALUE;
		for (int i = 0; i < k; i++) {
				
			float temp = Tweet.distance(tweet, centroids.get(i));
			if (temp < nearestDistance) {
				nearest = i;
				nearestDistance = temp;
			}
		}
		return nearest;
	}


    
    private static double totalSse(List<Tweet> centroids, HashMap<Integer, List<Tweet>> clusterPoints)
    {
        double SSE = 0;
        for(int i=0;i<k;i++)
        {
            double temp = 0;
            for(Tweet tweet :clusterPoints.get(i))
            {
                float distance = Tweet.distance(tweet, centroids.get(i));
                distance = distance * distance;
                temp += distance;
            }
            SSE += temp;
        }				
        return SSE;
    }
    
    
    private static void writeResult(String output, HashMap<Integer, List<Tweet>> clusterPoints) throws IOException
    {
        
        File outputFile = new File(output);
        BufferedWriter w = new BufferedWriter(new FileWriter(outputFile));
        
        for(int i = 0; i < clusterPoints.size();i++)
        {
            w.write(i+1 + "\t");
            for(Tweet tweet : clusterPoints.get(i))
            {
                w.write(tweet.id + ", ");
            }
            w.write("\n");
        }	
        w.close();
    }
}