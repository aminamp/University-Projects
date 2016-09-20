library(MASS)
library(class)
library(e1071)
pima <- read.table("http://archive.ics.uci.edu/ml/machine-learning-databases/pima-indians-diabetes/pima-indians-diabetes.data",header=F,sep=",")

for (i in 1:10 ) {
  indexes = sample(1:nrow(pima), size=0.1*nrow(pima))
  test = pima[indexes,]
  train = pima[-indexes,]
  model <- naiveBayes(as.factor(train$V9) ~ ., data = train)
  pred <- predict(model, test[,1:8])
  accuracy[i] <- sum(pred == test[,9])/length(pred)
}

accuracy * 100
mean(accuracy * 100)
