library(rpart)
library(rattle)
library(rpart.plot)
library(ggplot2)
library(lattice)
library(caret)
library(e1071)
data("kyphosis")
str(kyphosis)
model.frame(Kyphosis~., data = kyphosis)
kyphosis$Kyphosis
k <- rpart( Kyphosis~., data = kyphosis, method = "class", parms = list(split = 'information'), minsplit = 2, minbucket = 1 )
k$variable.importance
plot(k)
text(k)
prp(k)		# create a nicer Tree
fit <- rpart(Kyphosis ~ Age + Number + Start, data = kyphosis)
fit2 <- rpart(Kyphosis ~ Age + Number + Start, data = kyphosis, parms = list(prior = c(.65,.35), split = "information"))
par(mfrow = c(1,2), xpd = NA)
plot(fit, uniform = TRUE, margin = 0.1)
text(fit, use.n=TRUE, all=TRUE)
prp(fit)		#create a nicer Tree
plot(fit2, uniform = TRUE, margin = 0.1)
text(fit2, use.n=TRUE, all=TRUE)
prp(fit2)		#create a nicer Tree

# Prune the Tree
printcp(fit)
pfit<-prune(fit, cp= .01)
plot(pfit, uniform=TRUE, main="Pruned Classification Tree for Kyphosis")
text(pfit, use.n=TRUE, all=TRUE, cex=.8)

# Split Data 80% - 20% and test
#dim(kyphosis)
indexes = sample(1:nrow(kyphosis), size=0.2*nrow(kyphosis))
test = kyphosis[indexes,]
#dim(test)
train = kyphosis[-indexes,]
#dim(train)
Trainfit <- rpart(Kyphosis ~ Age + Number + Start, data = train)
predictfit<-prune(Trainfit, cp= .01)
prp(predictfit)
Trainfit
Prfit<-predict(predictfit, newdata=test ,type = "class")
Prfit
confusionMatrix(Prfit, test$Kyphosis)

# Split Data 90% - 10% and test
#dim(kyphosis)
indexes = sample(1:nrow(kyphosis), size=0.1*nrow(kyphosis))
test2 = kyphosis[indexes,]
#dim(test)
train2 = kyphosis[-indexes,]
#dim(train)
Trainfit2 <- rpart(Kyphosis ~ Age + Number + Start, data = train2)
predictfit2<-prune(Trainfit2, cp= .01)
prp(predictfit2)
Trainfit2
Prfit2<-predict(predictfit2, newdata=test2 ,type = "class")
Prfit2
confusionMatrix(Prfit2, test2$Kyphosis)

