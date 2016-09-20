library(MASS)
library(class)
library(e1071)
pima <- read.table("http://archive.ics.uci.edu/ml/machine-learning-databases/pima-indians-diabetes/pima-indians-diabetes.data",header=F,sep=",")


for (i in 1:10 ) {
  indexes = sample(1:nrow(pima), size=0.1*nrow(pima))
  test = pima[indexes,]
  train = pima[-indexes,]
  pred.knn <- knn(train[,1:8], test[,1:8], cl=as.factor(train[,9]), k=3)
  accuracy[i] <- sum(pred.knn == test[,9])/length(pred.knn)
}
mean(accuracy * 100)

