//
//  IAPHelper.m
//  GOE
//
//  Created by Limin on 12-4-1.
//  Copyright 2011年 Elex. All rights reserved.
//

#import "IAPHelper.h"

@implementation IAPHelper

@synthesize productIdentifiers = _productIdentifiers;
@synthesize products = _products;
@synthesize request = _request;

- (void)dealloc
{
	[_productIdentifiers release];
	[_products release];
	[_request release];
	[super dealloc];
}

- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers
{
	if ((self = [super init]))
	{
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
		_productIdentifiers = productIdentifiers;
		[self requestProducts];
	}
	return self;
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
	self.products = response.products;
	self.request = nil;
	
    [[NSNotificationCenter defaultCenter] postNotificationName:kProductsLoadedNotification object:_products userInfo:nil];
}

- (void)requestProducts
{
	SKProductsRequest* pr = [[SKProductsRequest alloc] initWithProductIdentifiers:_productIdentifiers];
	self.request = pr;
	[pr release];
	_request.delegate = self;
	[_request start];
}

- (void)recordTransaction:(SKPaymentTransaction *)transaction
{
	// Optional: Record the transaction on the server side...    
}

- (void)provideContent:(NSString *)productIdentifier myData:(NSData*)productData
{
}

- (void)completeTransaction:(SKPaymentTransaction *)transaction
{
	[self recordTransaction: transaction];
	[self provideContent:transaction.payment.productIdentifier myData:transaction.transactionReceipt];
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];	
}

- (void)restoreTransaction:(SKPaymentTransaction *)transaction
{
	[self recordTransaction: transaction];
	[self provideContent: transaction.originalTransaction.payment.productIdentifier myData:transaction.transactionReceipt];
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];	
}

-(void)purchaseFailed:(NSError*)error
{
}

- (void)failedTransaction:(SKPaymentTransaction *)transaction
{
	[self purchaseFailed:transaction.error];
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
	for (SKPaymentTransaction *transaction in transactions)
	{
		switch (transaction.transactionState)
		{
			case SKPaymentTransactionStatePurchased:
				[self completeTransaction:transaction];
				break;
			case SKPaymentTransactionStateFailed:
				[self failedTransaction:transaction];
				break;
			case SKPaymentTransactionStateRestored:
				[self restoreTransaction:transaction];
			default:
				break;
		}
	}
}

- (void)buyProductIdentifier:(NSString *)productIdentifier
{
	SKPayment *payment = [SKPayment paymentWithProductIdentifier:productIdentifier];
	[[SKPaymentQueue defaultQueue] addPayment:payment];    
}

@end
