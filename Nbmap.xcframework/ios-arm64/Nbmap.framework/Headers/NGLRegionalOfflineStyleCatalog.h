#import <Foundation/Foundation.h>

#import "NGLFoundation.h"

NS_ASSUME_NONNULL_BEGIN

NGL_EXPORT
@interface NGLRegionalOfflineStyleCatalog : NSObject
@property (class, nonatomic, readonly, copy) NSArray<NSString *> *styleNames;
+ (nullable NSURL *)uriForName:(NSString *)name;
+ (nullable NSString *)logicalNameForStyleURL:(NSURL *)styleURL;
+ (void)registerMapStyleForMapView:(id)mapView styleURL:(nullable NSURL *)styleURL;
@end

NS_ASSUME_NONNULL_END
