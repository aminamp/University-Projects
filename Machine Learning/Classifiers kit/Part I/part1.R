library(MASS)
library(class)
library(e1071)
pima <- read.table("http://archive.ics.uci.edu/ml/machine-learning-databases/pima-indians-diabetes/pima-indians-diabetes.data",header=F,sep=",")


hist(pima$V1,main="Histogram for Air Passengers",xlab="Number of times pregnant")
hist(pima$V2,main="Histogram for Pima Dataset",xlab="Plasma glucose concentration")
hist(pima$V3,main="Histogram for Pima Dataset",xlab="Diastolic blood pressure (mm Hg)")
hist(pima$V4,main="Histogram for Pima Dataset",xlab="Triceps skin fold thickness (mm)")
hist(pima$V5,main="Histogram for Pima Dataset",xlab="2-Hour serum insulin (mu U/ml)")
hist(pima$V6,main="Histogram for Pima Dataset",xlab="Body mass index")
hist(pima$V7,main="Histogram for Pima Dataset",xlab="Diabetes pedigree function")
hist(pima$V8,main="Histogram for Pima Dataset",xlab="Age")
barplot(pima$V1, xlab="Number of times pregnant")
barplot(pima$V2, xlab="Plasma glucose concentration")
barplot(pima$V3, xlab="Diastolic blood pressure (mm Hg)")
barplot(pima$V4, xlab="Triceps skin fold thickness (mm)")
barplot(pima$V5, xlab="2-Hour serum insulin (mu U/ml)")
barplot(pima$V6, xlab="Body mass index")
barplot(pima$V7, xlab="Diabetes pedigree function")
barplot(pima$V8, xlab="Age")


cor(pima$V1,pima$V9)	
cor(pima$V2,pima$V9)		
cor(pima$V3,pima$V9)	
cor(pima$V4,pima$V9)	
cor(pima$V5,pima$V9)	
cor(pima$V6,pima$V9)	
cor(pima$V7,pima$V9)	
cor(pima$V8,pima$V9)	

#find correlation between all pairs 
correlationMatrix <- cor(pima[,1:8])		
for (i in 1:8 ){correlationMatrix[i,i]=0}
which.max(print(correlationMatrix))


