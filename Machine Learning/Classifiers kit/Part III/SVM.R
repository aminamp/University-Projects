library(MASS)
library(class)
library(e1071)
pima <- read.table("http://archive.ics.uci.edu/ml/machine-learning-databases/pima-indians-diabetes/pima-indians-diabetes.data",header=F,sep=",")


# SVM : Linear
for (i in 1:10 ){
  indexes = sample(1:nrow(pima), size=0.1*nrow(pima))
  test = pima[indexes,]
  train = pima[-indexes,]
  svm_model <- svm(as.factor(train$V9)~., train, type='C', kernel='linear')
  pred <- predict(svm_model, test[,1:8])
  accuracy[i] <- sum(pred == test[,9])/length(pred)
}
accuracy * 100
mean(accuracy * 100)


#SVM : polynomial
for (i in 1:10 ){
  indexes = sample(1:nrow(pima), size=0.1*nrow(pima))
  test = pima[indexes,]
  train = pima[-indexes,]
  svm_model <- svm(as.factor(train$V9)~., train, type='C', kernel='polynomial', degree=3)
  pred <- predict(svm_model, test[,1:8])
  accuracy[i] <- sum(pred == test[,9])/length(pred)
}
accuracy * 100
mean(accuracy * 100)


#SVM : Radial without tune
for (i in 1:10 ){
  indexes = sample(1:nrow(pima), size=0.1*nrow(pima))
  test = pima[indexes,]
  train = pima[-indexes,]
  svm_model <- svm(as.factor(train$V9)~., train, type='C', kernel='radial', cost=1, gamma=0.5)
  pred <- predict(svm_model, test[,1:8])
  accuracy[i] <- sum(pred == test[,9])/length(pred)
}
accuracy * 100
mean(accuracy * 100)


#SVM : Sigmoid 
for (i in 1:10 ){
  indexes = sample(1:nrow(pima), size=0.1*nrow(pima))
  test = pima[indexes,]
  train = pima[-indexes,]
  svm_model <- svm(as.factor(train$V9)~., train, type='C', kernel='sigmoid')
  pred <- predict(svm_model, test[,1:8])
  accuracy[i] <- sum(pred == test[,9])/length(pred)
}
accuracy * 100
mean(accuracy * 100)
     

