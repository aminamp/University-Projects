import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Tweet
{
	
	String id;
	String text;
	int cluster;

	public Tweet(String id, String text)
    {
		super();
		this.id = id;
		this.text = text;
	}

	@Override
	public String toString()
    {
		return "Tweet ["+ text+"]";
	}

	public int getCluster()
    {
		return cluster;
	}

	public void setCluster(int cluster)
    {
		this.cluster = cluster;
	}
	
	public static float distance(Tweet t1, Tweet t2)
    {
		float dist = 0;
		
		HashSet<String> text1Set = new HashSet<String>(Arrays.asList(t1.text.toLowerCase().split(" ")));
		HashSet<String> text2Set = new HashSet<String>(Arrays.asList(t2.text.toLowerCase().split(" ")));
		
		
		Set<String> union = (Set<String>) text1Set.clone();
		union.addAll(text2Set);
				
		Set<String> intersection = (Set<String>) text1Set.clone();
		intersection.retainAll(text2Set);
			
		dist = 1.0f - (float)intersection.size() / (float) union.size();
		return dist;
	}
}
