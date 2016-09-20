public class Point{
	
	int id;
	float x,y;
	int cluster;

	public Point(int id, float x, float y)
    {
		super();
		this.id = id;
		this.x = x;
		this.y = y;
	}

	@Override
	public String toString()
    {
		return id +"";
	}

	public void setCluster(int cluster)
    {
		this.cluster = cluster;
	}
    
    public int getCluster()
    {
        return cluster;
    }
	
	public static double Distance(Point p1, Point p2)
    {
		double dist = 0;
		dist = Math.sqrt( (p1.x- p2.x)*(p1.x- p2.x) + (p1.y - p2.y)*(p1.y - p2.y) );
		return dist;
	}
	
}
