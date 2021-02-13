
# Naive Bayes

Naive Bayes is a simple technique for constructing classifiers: models that assign class labels to problem instances, represented as vectors of feature values, where the class labels are drawn from some finite set. There is not a single algorithm for training such classifiers, but a family of algorithms based on a common principle: all naive Bayes classifiers assume that the value of a particular feature is independent of the value of any other feature, given the class variable. For example, a fruit may be considered to be an apple if it is red, round, and about 10 cm in diameter. A naive Bayes classifier considers each of these features to contribute independently to the probability that this fruit is an apple, regardless of any possible correlations between the color, roundness, and diameter features.

For some types of probability models, naive Bayes classifiers can be trained very efficiently in a supervised learning setting. In many practical applications, parameter estimation for naive Bayes models uses the method of maximum likelihood; in other words, one can work with the naive Bayes model without accepting Bayesian probability or using any Bayesian methods.

Despite their naive design and apparently oversimplified assumptions, naive Bayes classifiers have worked quite well in many complex real-world situations. In 2004, an analysis of the Bayesian classification problem showed that there are sound theoretical reasons for the apparently implausible efficacy of naive Bayes classifiers.Still, a comprehensive comparison with other classification algorithms in 2006 showed that Bayes classification is outperformed by other approaches, such as boosted trees or random forests.

An advantage of naive Bayes is that it only requires a small number of training data to estimate the parameters necessary for classification.

## Bayesian Estimator
An estimator is Bayesian if it uses the Bayes theorem to predict the most likely class of some observed data.
Because the class of data is an unknown parameter and not a random variable, it is not possible to express the probability of that class using the standard concept of probability.
Bayesian probability uses a different notion of probability which quantifies our state of knowledge about the truth of an assertion.

***Bayes theorem allows us to compute the most likely class for some observed data, if you know something about how the data depends on the classes.***

The probability of a class assuming some observed data is expressed as P(C|D). The probability of the data assuming some class C is expressed as P(D|C).
The Bayes theorem is shown here:
    
>    **P( C|D ) = ( P( D|C ) * P( C ) ) / ( P( D ) )**

For the naive gaussian Bayesian classifier, the data, D, is a vector of samples. We assume that the samples are independent and that they follow a Gaussian distribution.

The parameters of the gaussian for each class will be computed during the training of the classifier. For each gaussian, the mean and standard deviation is computed.
Also, if some information about the class is available, and some classes are more or less likely, then this knowledge is encoded in the prior probability P( C ).
