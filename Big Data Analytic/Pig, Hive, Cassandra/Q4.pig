business = LOAD '/yelpdatafall/business/business.csv' USING PigStorage('^') as (business_id:chararray, full_address:chararray, categories:chararray);
NotCAbusiness = filter business by NOT(full_address matches '.*CA.*'); 

review = LOAD '/yelpdatafall/review/review.csv' using PigStorage('^') as (review_id:chararray, user_id:chararray, business_id:chararray, stars:double);
review_group = GROUP review by business_id;
count =  FOREACH review_group generate group as business_id, COUNT(review.stars) as stars_count;

cogroup_relation = COGROUP NotCAbusiness by business_id, count by business_id;
Clean_data = LIMIT cogroup_relation 6;
Clean_data = FOREACH Clean_data generate $1;
store Clean_data into '/axa142831/CasQ4' using PigStorage('^');


//hdfs dfs -cat /axa142831/CasQ4/*




	
