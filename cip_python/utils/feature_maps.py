import pdb
import math
import numpy as np

class FeatureMap:
    """Base class for mapping feature vectors from one space to another.

    Parameters
    ----------
    im_feature_vecs: list of feature images
        Each element of the list is a scalar image (all images must have the
        same dimension and size) representing a given dimension in the input
        feature space. For example, one image may be HU intensity values,
        another may be distance values to some structure, etc.    

    """
    def __init__(self, feature_vecs):
	self.feature_vecs = feature_vecs

class PolynomialFeatureMap(FeatureMap):    
    """Class for computing polynomial elements given a feature vector

    Parameters
    ----------
    im_feature_vecs: list of feature images
        Each element of the list is a scalar image (all images must have the
        same dimension and size) representing a given dimension in the input
        feature space. For example, one image may be HU intensity values,
        another may be distance values to some structure, etc.    

    orders: list of integers 
        Each integer is interpreted as a requested polynomial expansion order.
        0 will return a constant (1), 1 will simply return the input feature
        vectors, 2 will produce a binomial expansion, and so on. Multiple
        integers can be specified, e.g. [1, 2] will return the original feature
        vectors as well as the corresponding binomial expansion. Repeats of the
        same integer will be ignored, and the list will be sorted from low to
        high (e.g. [2, 1, 2] would be converted to [1, 2]).
        
    """
    def __init__(self, im_feature_vecs, input_orders, input_features):
      FeatureMap.__init__(im_feature_vecs)
      self._num_terms = -1
      num_terms_per_order = np.zeros(input_features.len)
      
    """function that computes the number of terms in the feature map given the list
     of orders 
    ----------
    return: none 
        
    """
    def compute_num_terms(self):
        """        
        Go through list of orders and add corresponding numterms
        """
        #http://mathforum.org/library/drmath/view/68607.html. m terms to the nth power:
        #(n+(m-1))!
        #---------- = "(n+m-1) choose (m-1)"
        #(n!)(m-1)!
        self.num_terms=0
        m = self.input_features.len
        f = math.factorial
        for x in range(0, self.list_of_orders.len):
            n = self.list_of_orders[x]
            self.num_terms_per_order[x] = f(n+m-1) /(f(n) * f(m-1))
            self.num_terms+=self.num_terms_per_order[x]
        
    def get_mapped_feature_vecs(self, list_of_features):
        """
        Get all the mapped feature vectors following polynomial expansion
        """
        pass
        
    def get_mapped_feature_vec_element(self, element_index, list_of_features):
        """
        Get the mapped feature vector at a particular element 
        """
        
        #first find the order and location of the particular element
        order_index = 0
        cumul_numterms = self.num_terms_per_order[order_index]
        element_within_order = element_index
        while cumul_numterms < (element_index+1):          
            order_index=order_index+1
            cumul_numterms+=self.num_terms_per_order[order_index]
            element_within_order=element_within_order-self.num_terms_per_order[order_index]
            
        #now now through a case statement for the established orders and terms
        if self.list_of_orders[order_index] is 1:
            return list_of_features[element_index]
        if self.list_of_orders[order_index] is 2:
            if element_within_order is 0:
                return list_of_features[0]*list_of_features[0]
            if element_within_order is 1:
                return list_of_features[0]*list_of_features[1]
            if element_within_order is 2:
                return list_of_features[1]*list_of_features[1]        
