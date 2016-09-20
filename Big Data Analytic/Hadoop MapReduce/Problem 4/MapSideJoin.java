import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class MapSideJoin {

	public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException, URISyntaxException {
		
		Configuration conf=new Configuration();
		String[] otherArgs=new GenericOptionsParser(conf,args).getRemainingArgs();
		
		if(otherArgs.length!=3)
		{
			System.err.println("Wrong Number Of Arguments");
			System.exit(2);
		}
		
		@SuppressWarnings("deprecation")
		Job job1=new Job(conf,"Filter Business Entries");
		
		job1.setJarByClass(MapSideJoin.class);

		Path inputFile=new Path(otherArgs[0]);  //bussiness.csv
        Path inputFile1=new Path(otherArgs[1]);  //review.csv
		Path outputFile=new Path(otherArgs[2]);
		Path intermidiateFile=new Path("axa142831_business_entries");
				
		FileInputFormat.addInputPath(job1, inputFile);
		FileOutputFormat.setOutputPath(job1, intermidiateFile);
		
		job1.setOutputKeyClass(Text.class);
		job1.setOutputValueClass(Text.class);
		
		job1.setMapOutputKeyClass(Text.class);
		job1.setMapOutputValueClass(Text.class);
		
		job1.setMapperClass(BusinessFilterMapper.class);
		job1.setReducerClass(BusinessFilterReducer.class);
		
		FileInputFormat.setMinInputSplitSize(job1, 500000000);
		
		job1.waitForCompletion(true);
		
//-----------------------------------------------------------------------------------------
		
		@SuppressWarnings("deprecation")
		Job job2=new Job(conf,"Joiner");
		job2.setJarByClass(MapSideJoin.class);

		job2.setMapperClass(Mapjoin_mapper.class);
		
		job2.setNumReduceTasks(0);
		job2.setOutputKeyClass(Text.class);
		job2.setOutputValueClass(Text.class);
		
		job2.addCacheFile(new URI(intermidiateFile.getName()+"/part-r-00000"));
		
		FileInputFormat.addInputPath(job2, inputFile1);
		FileOutputFormat.setOutputPath(job2, outputFile);
		FileInputFormat.setMinInputSplitSize(job2, 500000000);
		
		job2.waitForCompletion(true);

		org.apache.hadoop.fs.FileSystem fs = org.apache.hadoop.fs.FileSystem.get(conf);
		fs.delete(intermidiateFile, true);		
	}
}