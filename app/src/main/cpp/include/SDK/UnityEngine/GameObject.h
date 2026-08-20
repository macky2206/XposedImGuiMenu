#pragma once
#include "BNM/BNMIncludes.hpp"

namespace UnityEngine {
	class GameObject : public BNM::IL2CPP::Il2CppObject
	{
		public:
		static BNM::Class StaticClass() {
			return BNM::Class("UnityEngine", "GameObject", BNM::Image("UnityEngine.CoreModule.dll"));
		}
		
		
		/* @brief Orig Type: UnityEngine.GameObject */
		template <typename T = UnityEngine::GameObject*> static T CreatePrimitive(int type) {
			static auto __bnm__method__ = (T(*)(int))BNM::GetExternMethod("UnityEngine.GameObject::CreatePrimitive");
			return (T)__bnm__method__(type);
		}
		/* @brief Orig Type: T */
		/* @brief Helper: call generic GetComponent<T>() by providing compile-time class(es) */
		template <typename T = void*> T GetComponentGeneric(const BNM::CompileTimeClass &compileType0) {
			auto methodBase = StaticClass().GetMethod("GetComponent", 0);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod();
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T GetComponentGeneric(const BNM::Class &cls0) {
			return GetComponentGeneric<T>(cls0.GetCompileTimeClass());
		}
		/* @brief Orig Type: UnityEngine.Component */
		template <typename T = BNM::IL2CPP::Il2CppObject*> T GetComponent(BNM::MonoType* type) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::MonoType*))BNM::GetExternMethod("UnityEngine.GameObject::GetComponent");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, type);
		}
		/* @brief Orig Type: System.Void */
		template <typename T = void> T GetComponentFastPath(BNM::MonoType* type, BNM::Types::nuint oneFurtherThanResultValue) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::MonoType*, BNM::Types::nuint))BNM::GetExternMethod("UnityEngine.GameObject::GetComponentFastPath");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, type, oneFurtherThanResultValue);
		}
		/* @brief Orig Type: UnityEngine.Component */
		template <typename T = BNM::IL2CPP::Il2CppObject*> T GetComponentInChildren(BNM::MonoType* type, bool includeInactive) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::MonoType*, bool))BNM::GetExternMethod("UnityEngine.GameObject::GetComponentInChildren");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, type, includeInactive);
		}
		/* @brief Orig Type: T */
		/* @brief Helper: call generic GetComponentInChildren<T>() by providing compile-time class(es) */
		template <typename T = void*> T GetComponentInChildrenGeneric(const BNM::CompileTimeClass &compileType0) {
			auto methodBase = StaticClass().GetMethod("GetComponentInChildren", 0);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod();
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T GetComponentInChildrenGeneric(const BNM::Class &cls0) {
			return GetComponentInChildrenGeneric<T>(cls0.GetCompileTimeClass());
		}
		/* @brief Orig Type: T */
		/* @brief Helper: call generic GetComponentInChildren<T>() by providing compile-time class(es) */
		template <typename T = void*> T GetComponentInChildren_1Generic(const BNM::CompileTimeClass &compileType0, bool includeInactive) {
			auto methodBase = StaticClass().GetMethod("GetComponentInChildren", 1);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod(includeInactive);
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T GetComponentInChildren_1Generic(const BNM::Class &cls0, bool includeInactive) {
			return GetComponentInChildren_1Generic<T>(cls0.GetCompileTimeClass(), includeInactive);
		}
		/* @brief Orig Type: UnityEngine.Component */
		template <typename T = BNM::IL2CPP::Il2CppObject*> T GetComponentInParent(BNM::MonoType* type, bool includeInactive) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::MonoType*, bool))BNM::GetExternMethod("UnityEngine.GameObject::GetComponentInParent");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, type, includeInactive);
		}
		/* @brief Orig Type: T */
		/* @brief Helper: call generic GetComponentInParent<T>() by providing compile-time class(es) */
		template <typename T = void*> T GetComponentInParentGeneric(const BNM::CompileTimeClass &compileType0) {
			auto methodBase = StaticClass().GetMethod("GetComponentInParent", 0);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod();
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T GetComponentInParentGeneric(const BNM::Class &cls0) {
			return GetComponentInParentGeneric<T>(cls0.GetCompileTimeClass());
		}
		/* @brief Orig Type: T */
		/* @brief Helper: call generic GetComponentInParent<T>() by providing compile-time class(es) */
		template <typename T = void*> T GetComponentInParent_1Generic(const BNM::CompileTimeClass &compileType0, bool includeInactive) {
			auto methodBase = StaticClass().GetMethod("GetComponentInParent", 1);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod(includeInactive);
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T GetComponentInParent_1Generic(const BNM::Class &cls0, bool includeInactive) {
			return GetComponentInParent_1Generic<T>(cls0.GetCompileTimeClass(), includeInactive);
		}
		/* @brief Orig Type: System.Array */
		template <typename T = BNM::IL2CPP::Il2CppObject*> T GetComponentsInternal(BNM::MonoType* type, bool useSearchTypeAsArrayReturnType, bool recursive, bool includeInactive, bool reverse, BNM::IL2CPP::Il2CppObject* resultList) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::MonoType*, bool, bool, bool, bool, BNM::IL2CPP::Il2CppObject*))BNM::GetExternMethod("UnityEngine.GameObject::GetComponentsInternal");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, type, useSearchTypeAsArrayReturnType, recursive, includeInactive, reverse, resultList);
		}
		/* @brief Orig Type: T[] */
		/* @brief Helper: call generic GetComponents<T>() by providing compile-time class(es) */
		template <typename T = void*> T GetComponentsGeneric(const BNM::CompileTimeClass &compileType0) {
			auto methodBase = StaticClass().GetMethod("GetComponents", 0);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod();
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T GetComponentsGeneric(const BNM::Class &cls0) {
			return GetComponentsGeneric<T>(cls0.GetCompileTimeClass());
		}
		/* @brief Orig Type: System.Void */
		/* @brief Helper: call generic GetComponents<T>() by providing compile-time class(es) */
		template <typename T = void> T GetComponents_1Generic(const BNM::CompileTimeClass &compileType0, void* /*GENERICTYPE*/ results) {
			auto methodBase = StaticClass().GetMethod("GetComponents", 1);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod(results);
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void> T GetComponents_1Generic(const BNM::Class &cls0, void* /*GENERICTYPE*/ results) {
			return GetComponents_1Generic<T>(cls0.GetCompileTimeClass(), results);
		}
		/* @brief Orig Type: T[] */
		/* @brief Helper: call generic GetComponentsInChildren<T>() by providing compile-time class(es) */
		template <typename T = void*> T GetComponentsInChildrenGeneric(const BNM::CompileTimeClass &compileType0, bool includeInactive) {
			auto methodBase = StaticClass().GetMethod("GetComponentsInChildren", 1);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod(includeInactive);
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T GetComponentsInChildrenGeneric(const BNM::Class &cls0, bool includeInactive) {
			return GetComponentsInChildrenGeneric<T>(cls0.GetCompileTimeClass(), includeInactive);
		}
		/* @brief Orig Type: System.Void */
		/* @brief Helper: call generic GetComponentsInChildren<T>() by providing compile-time class(es) */
		template <typename T = void> T GetComponentsInChildren_1Generic(const BNM::CompileTimeClass &compileType0, bool includeInactive, void* /*GENERICTYPE*/ results) {
			auto methodBase = StaticClass().GetMethod("GetComponentsInChildren", 2);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod(includeInactive, results);
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void> T GetComponentsInChildren_1Generic(const BNM::Class &cls0, bool includeInactive, void* /*GENERICTYPE*/ results) {
			return GetComponentsInChildren_1Generic<T>(cls0.GetCompileTimeClass(), includeInactive, results);
		}
		/* @brief Orig Type: T[] */
		/* @brief Helper: call generic GetComponentsInChildren<T>() by providing compile-time class(es) */
		template <typename T = void*> T GetComponentsInChildren_2Generic(const BNM::CompileTimeClass &compileType0) {
			auto methodBase = StaticClass().GetMethod("GetComponentsInChildren", 0);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod();
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T GetComponentsInChildren_2Generic(const BNM::Class &cls0) {
			return GetComponentsInChildren_2Generic<T>(cls0.GetCompileTimeClass());
		}
		/* @brief Orig Type: System.Void */
		/* @brief Helper: call generic GetComponentsInParent<T>() by providing compile-time class(es) */
		template <typename T = void> T GetComponentsInParentGeneric(const BNM::CompileTimeClass &compileType0, bool includeInactive, void* /*GENERICTYPE*/ results) {
			auto methodBase = StaticClass().GetMethod("GetComponentsInParent", 2);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod(includeInactive, results);
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void> T GetComponentsInParentGeneric(const BNM::Class &cls0, bool includeInactive, void* /*GENERICTYPE*/ results) {
			return GetComponentsInParentGeneric<T>(cls0.GetCompileTimeClass(), includeInactive, results);
		}
		/* @brief Orig Type: T[] */
		/* @brief Helper: call generic GetComponentsInParent<T>() by providing compile-time class(es) */
		template <typename T = void*> T GetComponentsInParent_1Generic(const BNM::CompileTimeClass &compileType0, bool includeInactive) {
			auto methodBase = StaticClass().GetMethod("GetComponentsInParent", 1);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod(includeInactive);
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T GetComponentsInParent_1Generic(const BNM::Class &cls0, bool includeInactive) {
			return GetComponentsInParent_1Generic<T>(cls0.GetCompileTimeClass(), includeInactive);
		}
		/* @brief Orig Type: System.Boolean */
		/* @brief Helper: call generic TryGetComponent<T>() by providing compile-time class(es) */
		template <typename T = bool> T TryGetComponentGeneric(const BNM::CompileTimeClass &compileType0, void** component) {
			auto methodBase = StaticClass().GetMethod("TryGetComponent", 1);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod(component);
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = bool> T TryGetComponentGeneric(const BNM::Class &cls0, void** component) {
			return TryGetComponentGeneric<T>(cls0.GetCompileTimeClass(), component);
		}
		/* @brief Orig Type: System.Boolean */
		template <typename T = bool> T TryGetComponent(BNM::MonoType* type, BNM::IL2CPP::Il2CppObject** component) {
			static BNM::Method<T> __bnm__method__ = StaticClass().GetMethod("TryGetComponent", 2);
			return __bnm__method__[(BNM::IL2CPP::Il2CppObject*)this](type, component);
		}
		/* @brief Orig Type: UnityEngine.Component */
		template <typename T = BNM::IL2CPP::Il2CppObject*> T TryGetComponentInternal(BNM::MonoType* type) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::MonoType*))BNM::GetExternMethod("UnityEngine.GameObject::TryGetComponentInternal");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, type);
		}
		/* @brief Orig Type: System.Void */
		template <typename T = void> T TryGetComponentFastPath(BNM::MonoType* type, BNM::Types::nuint oneFurtherThanResultValue) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::MonoType*, BNM::Types::nuint))BNM::GetExternMethod("UnityEngine.GameObject::TryGetComponentFastPath");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, type, oneFurtherThanResultValue);
		}
		/* @brief Orig Type: UnityEngine.Component */
		template <typename T = BNM::IL2CPP::Il2CppObject*> T Internal_AddComponentWithType(BNM::MonoType* componentType) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::MonoType*))BNM::GetExternMethod("UnityEngine.GameObject::Internal_AddComponentWithType");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, componentType);
		}
		/* @brief Orig Type: UnityEngine.Component */
		template <typename T = BNM::IL2CPP::Il2CppObject*> T AddComponent(BNM::MonoType* componentType) {
			static BNM::Method<T> __bnm__method__ = StaticClass().GetMethod("AddComponent", 1);
			return __bnm__method__[(BNM::IL2CPP::Il2CppObject*)this](componentType);
		}
		/* @brief Orig Type: T */
		/* @brief Helper: call generic AddComponent<T>() by providing compile-time class(es) */
		template <typename T = void*> T AddComponentGeneric(const BNM::CompileTimeClass &compileType0) {
			auto methodBase = StaticClass().GetMethod("AddComponent", 0);
			auto genericMethod = methodBase.GetGeneric({compileType0});
			if (!genericMethod.IsValid()) return (T)nullptr;
			BNM::Method<T> typedMethod = genericMethod;
			typedMethod[(BNM::IL2CPP::Il2CppObject*)this];
			if (!typedMethod.IsValid()) return (T)nullptr;
			return typedMethod();
		}
		/* @brief Helper overload: accept BNM::Class and convert to CompileTimeClass */
		template <typename T = void*> T AddComponentGeneric(const BNM::Class &cls0) {
			return AddComponentGeneric<T>(cls0.GetCompileTimeClass());
		}
		/* @brief Orig Type: UnityEngine.Transform */
		template <typename T = BNM::IL2CPP::Il2CppObject*> T get_transform() {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*))BNM::GetExternMethod("UnityEngine.GameObject::get_transform");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this);
		}
		/* @brief Orig Type: System.Int32 */
		template <typename T = int> T get_layer() {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*))BNM::GetExternMethod("UnityEngine.GameObject::get_layer");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this);
		}
		/* @brief Orig Type: System.Void */
		template <typename T = void> T set_layer(int $value) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, int))BNM::GetExternMethod("UnityEngine.GameObject::set_layer");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, $value);
		}
		/* @brief Orig Type: System.Void */
		template <typename T = void> T SetActive(bool $value) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, bool))BNM::GetExternMethod("UnityEngine.GameObject::SetActive");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, $value);
		}
		/* @brief Orig Type: System.Boolean */
		template <typename T = bool> T get_activeSelf() {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*))BNM::GetExternMethod("UnityEngine.GameObject::get_activeSelf");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this);
		}
		/* @brief Orig Type: System.Boolean */
		template <typename T = bool> T get_activeInHierarchy() {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*))BNM::GetExternMethod("UnityEngine.GameObject::get_activeInHierarchy");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this);
		}
		/* @brief Orig Type: System.Void */
		template <typename T = void> T set_tag(BNM::Structures::Mono::String* $value) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::Structures::Mono::String*))BNM::GetExternMethod("UnityEngine.GameObject::set_tag");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, $value);
		}
		/* @brief Orig Type: System.Boolean */
		template <typename T = bool> T CompareTag(BNM::Structures::Mono::String* tag) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::Structures::Mono::String*))BNM::GetExternMethod("UnityEngine.GameObject::CompareTag");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, tag);
		}
		/* @brief Orig Type: UnityEngine.GameObject */
		template <typename T = UnityEngine::GameObject*> static T FindGameObjectWithTag(BNM::Structures::Mono::String* tag) {
			static auto __bnm__method__ = (T(*)(BNM::Structures::Mono::String*))BNM::GetExternMethod("UnityEngine.GameObject::FindGameObjectWithTag");
			return (T)__bnm__method__(tag);
		}
		/* @brief Orig Type: UnityEngine.GameObject[] */
		template <typename T = BNM::Structures::Mono::Array<BNM::IL2CPP::Il2CppObject*>*> static T FindGameObjectsWithTag(BNM::Structures::Mono::String* tag) {
			static auto __bnm__method__ = (T(*)(BNM::Structures::Mono::String*))BNM::GetExternMethod("UnityEngine.GameObject::FindGameObjectsWithTag");
			return (T)__bnm__method__(tag);
		}
		/* @brief Orig Type: System.Void */
		template <typename T = void> T SendMessage(BNM::Structures::Mono::String* methodName, BNM::IL2CPP::Il2CppObject* $value, int options) {
			static auto __bnm__method__ = (T(*)(BNM::IL2CPP::Il2CppObject*, BNM::Structures::Mono::String*, BNM::IL2CPP::Il2CppObject*, int))BNM::GetExternMethod("UnityEngine.GameObject::SendMessage");
			return (T)__bnm__method__((BNM::IL2CPP::Il2CppObject*)this, methodName, $value, options);
		}
		/* @brief Orig Type: System.Void */
		template <typename T = void> static T Internal_CreateGameObject(UnityEngine::GameObject* self, BNM::Structures::Mono::String* name) {
			static auto __bnm__method__ = (T(*)(UnityEngine::GameObject*, BNM::Structures::Mono::String*))BNM::GetExternMethod("UnityEngine.GameObject::Internal_CreateGameObject");
			return (T)__bnm__method__(self, name);
		}
		/* @brief Orig Type: UnityEngine.GameObject */
		template <typename T = UnityEngine::GameObject*> static T Find(BNM::Structures::Mono::String* name) {
			static auto __bnm__method__ = (T(*)(BNM::Structures::Mono::String*))BNM::GetExternMethod("UnityEngine.GameObject::Find");
			return (T)__bnm__method__(name);
		}
		/* @brief Orig Type: UnityEngine.GameObject */
		template <typename T = UnityEngine::GameObject*> T get_gameObject() {
			static BNM::Method<T> __bnm__method__ = StaticClass().GetMethod("get_gameObject", 0);
			return __bnm__method__[(BNM::IL2CPP::Il2CppObject*)this]();
		}
		
	};
}
