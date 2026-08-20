#pragma once

/* 	
// RVA: 0xA36CA0 Offset: 0xA36CA0 VA: 0xA36CA0
public void FBCOAEGAFIB() { } // CALL PURCHASE UI

// RVA: 0xA36D20 Offset: 0xA36D20 VA: 0xA36D20
public void FJKEDCNLOAK() { } // COMPLETE PURCHASE
*/

namespace Features {
    namespace freeShop {
        bool isEnabled = false;
        BNM::Method<void> g_PurchaseItemMethod;
        BNM::Method<void> g_CompletePurchaseMethod;

        void (*orig_PurchaseItem)(void *instance);
        void hooked_PurchaseItem(void *instance) {
            if (isEnabled) {
                g_CompletePurchaseMethod[instance].Call();
            } else {
                orig_PurchaseItem(instance);
            }
        }

        void initHook() {
            g_PurchaseItemMethod = BNM::Class("", "StorePurchase").GetMethod("njk");
            g_CompletePurchaseMethod = BNM::Class("", "StorePurchase").GetMethod("njl");

            BasicHook(g_PurchaseItemMethod.GetOffset(), hooked_PurchaseItem, orig_PurchaseItem);

            BNM_LOG_INFO("FreeShop feature initialized");
        }
    }// namespace FreeShop
}// namespace Features