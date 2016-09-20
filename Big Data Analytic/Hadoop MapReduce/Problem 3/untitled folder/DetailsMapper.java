import java.io.IOException;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class DetailsMapper extends Mapper<LongWritable, Text, Text, Text> {

	static String total_record = "";

	@Override
	protected void map(LongWritable baseAddress, Text line, Context context)
			throws IOException, InterruptedException {

		Text business_id = new Text();
		Text details = new Text();

		total_record = total_record.concat(line.toString());
		String[] fields = total_record.split("\\^");
		if (fields.length == 3) {
			if (1) {
				String full_address=fields[1].trim();
				String categories=fields[2].trim();
				String value="b:\t"+full_address+"\t"+categories;
				
				business_id.set(fields[0].trim());
				details.set(value);
				context.write(business_id, details);
			}
			total_record="";
		}
	}
}
