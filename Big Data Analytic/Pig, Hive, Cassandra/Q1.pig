business = LOAD '/yelpdatafall/business/business.csv' USING PigStorage('^') as (business_id:chararray, full_address:chararray, categories:chararray);
CAbusiness = filter business by (full_address matches '.*CA.*');
review = LOAD '/yelpdatafall/review/review.csv' using PigStorage('^') as (review_id:chararray, user_id:chararray, business_id:chararray, stars:double);
review_group = GROUP review by business_id;
stars_avg =  FOREACH review_group generate group as business_id, AVG(review.stars) as avg_ratings;

business_review = JOIN CAbusiness by business_id, stars_avg by business_id;
sorted_business = ORDER business_review BY avg_ratings DESC;
limit_business = LIMIT sorted_business 10;
limit_business = FOREACH limit_business generate $0,$1,$2;
store limit_business into '/axa142831/CasQ1' using PigStorage('^');


//hdfs dfs -cat /axa142831/CasQ1/*
