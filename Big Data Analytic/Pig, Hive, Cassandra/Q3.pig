business = LOAD '/yelpdatafall/business/business.csv' USING PigStorage('^') as (business_id:chararray, full_address:chararray, categories:chararray);

review = LOAD '/yelpdatafall/review/review.csv' using PigStorage('^') as (review_id:chararray, user_id:chararray, business_id:chararray, stars:double);

cogroup_relation = COGROUP business by business_id, review by business_id;
Result = LIMIT cogroup_relation 6;


STORE Result into '/axa142831/CasQ3' using PigStorage('^');


//hdfs dfs -cat /axa142831/CasQ3/*

