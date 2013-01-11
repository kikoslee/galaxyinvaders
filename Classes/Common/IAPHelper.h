//
//  IAPHelper.h
//  GOE
//
//  Created by Limin on 12-4-1.
//  Copyright 2011年 Elex. All rights reserved.
//

#import "StoreKit/StoreKit.h"

#define kProductsLoadedNotification         @"ProductsLoaded"

@interface IAPHelper : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>
{
    NSSet *_productIdentifiers;    
    NSArray *_products;
    SKProductsRequest *_request;
}

@property (nonatomic, retain) NSSet *productIdentifiers;
@property (nonatomic, retain) NSArray *products;
@property (nonatomic, retain) SKProductsRequest *request;

- (void)requestProducts;
- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers;
- (void)buyProductIdentifier:(NSString *)productIdentifier;

-(void)purchaseFailed:(NSError*)error;


@end
