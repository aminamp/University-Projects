import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URI;
import java.util.HashMap;

import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.FloatWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;


public class Mapjoin_mapper extends Mapper<LongWritable, Text, Text, FloatWritable> {

	static String total_record = "";
	static HashMap<String, String> map = new HashMap<String, String>();

	@Override
	protected void setup(Context context) throws IOException,
			InterruptedException {

		URI[] files = context.getCacheFiles();

		if (files.length == 0) {
			throw new FileNotFoundException("Distributed cache file not found");
		}
		FileSystem fs = FileSystem.get(context.getConfiguration());
		FSDataInputStream in = fs.open(new Path(files[0]));
		BufferedReader br = new BufferedReader(new InputStreamReader(in));
		readCacheFile(br);
	};

	private void readCacheFile(BufferedReader br) throws IOException {
		String line = br.readLine();
		while (line != null) {
			String[] fields = line.split("\t");
			map.put(fields[0].trim(), fields[1].trim());
			line = br.readLine();
		}
	}

	@Override
	protected void map(LongWritable key, Text line, Mapper<LongWritable, Text, Text, FloatWritable>.Context context)
			throws IOException, InterruptedException {

		Text user_id = new Text();
		FloatWritable stars = new FloatWritable(1);

		total_record = total_record.concat(line.toString());
		String[] fields = total_record.split("\\^");
		if (fields.length == 4) {
			if ( true ) {

				String business_id = fields[2].trim();

				String city = map.get(business_id);

				if (city != null) {

					if (city.contains("Stanford,")) {
						stars.set(Float.parseFloat(fields[3].trim()));
						user_id.set(fields[1].trim());
						context.write(user_id, stars);
					}
				}
			}
			total_record = "";

		}
	}
}