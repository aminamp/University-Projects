library(rpart)
library(rattle)
library(rpart.plot)
library(e1071)
library(caret)
library(lattice)
library(ggplot2)
data("solder")
str(solder)
k <- rpart(Solder ~ Opening + Solder + Mask + PadType + Panel + skips, data = solder, parms = list(split = 'information'))
k$variable.importance
plot(k)
text(k)
prp(k)
fit <- rpart(skips ~ Opening + Solder + Mask + PadType + Panel, data=solder, method='anova')
prp(fit)

# Prune the Tree
printcp(fit)
pfit<-prune(fit, cp= .01)
plot(pfit, uniform=TRUE, main="Pruned Classification Tree for Kyphosis")
text(pfit, use.n=TRUE, all=TRUE, cex=.8)

# Split Data 80% - 20% and test
#dim(solder)
indexes = sample(1:nrow(solder), size=0.2*nrow(solder))
test = solder[indexes,]
#dim(test)
train = solder[-indexes,]
#dim(train)
Trainfit <- rpart(skips ~ Opening + Solder + Mask + PadType + Panel, data = train)
predictfit<-prune(Trainfit, cp= .01)
prp(predictfit)
Trainfit
Prfit<-predict(predictfit, newdata=test ,type = "vector")
round(Prfit)
test$skips


# Split Data 90% - 10% and test
#dim(solder)
indexes = sample(1:nrow(solder), size=0.1*nrow(solder))
test2 = solder[indexes,]
#dim(test)
train2 = solder[-indexes,]
#dim(train)
Trainfit2 <- rpart(skips ~ Opening + Solder + Mask + PadType + Panel, data = train2)
predictfit2<-prune(Trainfit2, cp= .01)
prp(predictfit2)
Trainfit2
Prfit2<-predict(predictfit2, newdata=test2 ,type = "vector")
round(Prfit2)
test2$skips

