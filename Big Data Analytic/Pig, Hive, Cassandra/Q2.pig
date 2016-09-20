business = LOAD '/yelpdatafall/business/business.csv' USING PigStorage('^') as (business_id:chararray, full_address:chararray, categories:chararray);
NotCAbusiness = filter business by NOT(full_address matches '.*CA.*');  

review = LOAD '/yelpdatafall/review/review.csv' using PigStorage('^') as (review_id:chararray, user_id:chararray, business_id:chararray, stars:double);

review_group = GROUP review by business_id;
count =  FOREACH review_group generate group as business_id, COUNT(review.stars) as stars_count;

business_review = JOIN NotCAbusiness by business_id, count by business_id;
sorted_business = ORDER business_review BY stars_count DESC;
limit_business = LIMIT sorted_business 10;
limit_business = FOREACH limit_business generate $0,$1,$2;
store limit_business into '/axa142831/CasQ2' using PigStorage('^');



//hdfs dfs -cat /axa142831/CasQ2/*

